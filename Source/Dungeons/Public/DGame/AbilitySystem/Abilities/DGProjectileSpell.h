#pragma once

#include "CoreMinimal.h"
#include "DGame/AbilitySystem/Abilities/DGGameplayAbility.h"
#include "DGProjectileSpell.generated.h"


class ADGProjectile;

UCLASS()
class DUNGEONS_API UDGProjectileSpell : public UDGGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<ADGProjectile> ProjectileClass;
};
