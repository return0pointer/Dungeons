


#include "DGame/Character/DGCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/Player/DGPlayerController.h"
#include "DGame/Player/DGPlayerState.h"
#include "DGame/UI/HUD/DGHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADGCharacter::ADGCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f,0.f));
	SpringArmComponent->TargetArmLength = 750.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmComponent);
	Camera->bUsePawnControlRotation = false;	

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCharacterMovement()->BrakingFrictionFactor = 0.000001f;
	GetCharacterMovement()->MaxAcceleration = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 800.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ADGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ADGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
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
