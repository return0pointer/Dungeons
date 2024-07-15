

#pragma once

#include "CoreMinimal.h"
#include "DGame/AbilitySystem/Abilities/DGGameplayAbility.h"
#include "DGame/Interaction/CombatInterface.h"
#include "DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONS_API UDamageGameplayAbility : public UDGGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure, Category="Montage")
	bool GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages, FTaggedMontage& OutTaggedMontage) const;
};
