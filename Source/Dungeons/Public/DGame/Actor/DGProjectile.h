#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class DUNGEONS_API ADGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADGProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
protected:
	virtual void BeginPlay() override;
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result);
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
