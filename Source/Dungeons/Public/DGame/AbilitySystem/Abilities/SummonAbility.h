

#pragma once

#include "CoreMinimal.h"
#include "DGame/AbilitySystem/Abilities/DGGameplayAbility.h"
#include "SummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONS_API USummonAbility : public UDGGameplayAbility
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="Summoning")
	TArray<FVector> GetSpawnLocation();

	UFUNCTION(BlueprintPure, Category="Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Summoning")
	int32 NumMinions = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Summoning")
	float MaxSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Summoning")
	float SpawnSpread = 90.f;
};
