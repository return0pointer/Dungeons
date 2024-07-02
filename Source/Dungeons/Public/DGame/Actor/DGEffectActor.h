

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class DUNGEONS_API ADGEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADGEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

};
