#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "DGProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class DUNGEONS_API ADGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADGProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	void SetOwnerAvatar(AActor* InOwnerAvatar) { OwnerAvatar = InOwnerAvatar; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void PlayImpactEffects() const;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result);
	
private:

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan;

	bool bHit;

	UPROPERTY()
	TObjectPtr<AActor> OwnerAvatar = nullptr;

	

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	UAudioComponent* LoopingSoundComponent;
};
