#pragma once

#include "CoreMinimal.h"
#include "DamageGameplayAbility.h"
#include "DGProjectileSpell.generated.h"


class ADGProjectile;
class UGameplayEffect;

UCLASS()
class DUNGEONS_API UDGProjectileSpell : public UDamageGameplayAbility
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
