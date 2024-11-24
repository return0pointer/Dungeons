#include "DGame/Character/DGCharacter.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/Player/DGPlayerController.h"
#include "DGame/Player/DGPlayerState.h"
#include "DGame/UI/HUD/DGHUD.h"
#include "Dungeons/Dungeons.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADGCharacter::ADGCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-55.f, 0.f,0.f));
	SpringArmComponent->TargetArmLength = 900.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmComponent);
	Camera->bUsePawnControlRotation = false;	

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 250.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCharacterMovement()->BrakingFrictionFactor = 0.1f;
	GetCharacterMovement()->MaxAcceleration = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1200.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;	
}

void ADGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ADGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void ADGCharacter::SetInvulnerability_Implementation(bool Invulnerability, bool ChangeVisibility)
{
	if (Invulnerability)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	}
	if (ChangeVisibility)
	{
		GetMesh()->SetVisibility(!Invulnerability, true);
	}
}

UAnimMontage* ADGCharacter::GetJumpMontage_Implementation()
{
	return JumpMontage;
}

int32 ADGCharacter::GetPlayerLevel()
{
	const ADGPlayerState* DGPlayerState = GetPlayerState<ADGPlayerState>();
	check(DGPlayerState);
	return DGPlayerState->GetPlayerLevel();
}

void ADGCharacter::InitAbilityActorInfo()
{
	ADGPlayerState* DGPlayerState = GetPlayerState<ADGPlayerState>();
	check(DGPlayerState);
	DGPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DGPlayerState, this);	
	AbilitySystemComponent = DGPlayerState->GetAbilitySystemComponent();
	Cast<UDGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = DGPlayerState->GetAttributeSet();

	if (ADGPlayerController* DGPlayerController = Cast<ADGPlayerController>(GetController()))
	{
		if (ADGHUD* DGHud = Cast<ADGHUD>(DGPlayerController->GetHUD()))
		{
			DGHud->InitOverlay(DGPlayerController, DGPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
