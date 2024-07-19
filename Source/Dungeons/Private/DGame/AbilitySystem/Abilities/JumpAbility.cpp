#include "DGame/AbilitySystem/Abilities/JumpAbility.h"

#include "NiagaraFunctionLibrary.h"
#include "DGame/Interaction/CombatInterface.h"
#include "GameFramework/Character.h"

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CanJump = false;
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	CharacterToJump = Cast<ACharacter>(AvatarActor);
	const FVector MovementVector = CharacterToJump->ConsumeMovementInputVector();
	if (MovementVector.Length() > 0.001f)
	{
		constexpr float DirectionMultiplier = 100.f;
		const FVector TargetVector = AvatarActor->GetActorLocation() + MovementVector * DirectionMultiplier;
		ICombatInterface::Execute_UpdateFacingTarget(GetAvatarActorFromActorInfo(), TargetVector);
		CanJump = true;
	}
	
}