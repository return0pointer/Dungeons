

#pragma once

#include "CoreMinimal.h"
#include "DGame/AbilitySystem/Abilities/DGGameplayAbility.h"
#include "JumpAbility.generated.h"

class UNiagaraSystem;

UCLASS()
class DUNGEONS_API UJumpAbility : public UDGGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="_Properties")
	TSubclassOf<UGameplayEffect> JumpEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="_Properties")
	TObjectPtr<UNiagaraSystem> JumpEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="_Properties")
	TSubclassOf<AActor> ShadowActorClass;
	
	UPROPERTY(BlueprintReadOnly, Category="JumpAbility")
	ACharacter* CharacterToJump;

	UPROPERTY(BlueprintReadOnly)
	bool CanJump = false;
};
