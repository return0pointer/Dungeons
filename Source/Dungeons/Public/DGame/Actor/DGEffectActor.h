

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGEffectActor.generated.h"

class USphereComponent;

UCLASS()
class DUNGEONS_API ADGEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADGEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
