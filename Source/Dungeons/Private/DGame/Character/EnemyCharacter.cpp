#include "DGame/Character/EnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "DGame/DGGameplayTags.h"
#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/AbilitySystem/DGAbilitySystemLibrary.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"
#include "DGame/AI/DGAIController.h"
#include "DGame/UI/Widget/DGUserWidget.h"
#include "Dungeons/Dungeons.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UDGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->MaxAcceleration = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1200.f;
	
	AttributeSet = CreateDefaultSubobject<UDGAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	Level = 1;
	CharacterClass = ECharacterClass::Warrior;
	BaseWalkSpeed = 250.f;
	LifeSpanAfterDie = 5.f;
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
	DgAIController = Cast<ADGAIController>(NewController);
	DgAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	DgAIController->RunBehaviorTree(BehaviorTree);
	DgAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	DgAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnemyCharacter::SetupBinding()
{
	if (UDGUserWidget* HealthBarWidget = Cast<UDGUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		HealthBarWidget->SetWidgetController(this);
	}

	if (const UDGAttributeSet* DgAS = Cast<UDGAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DgAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DgAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->RegisterGameplayTagEvent(
			FDGGameplayTags::Get().Effects_HitReact,
		    EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &AEnemyCharacter::HitReactTagChanged);

		OnHealthChanged.Broadcast(DgAS->GetHealth());
		OnMaxHealthChanged.Broadcast(DgAS->GetMaxHealth());
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();

	if (HasAuthority())
	{
		UDGAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);		
	}

	SetupBinding();
}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AEnemyCharacter::Die()
{
	SetLifeSpan(LifeSpanAfterDie);
	Super::Die();	
}

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (DgAIController && DgAIController->GetBlackboardComponent())
	{
		DgAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);		
	}
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	UDGAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
