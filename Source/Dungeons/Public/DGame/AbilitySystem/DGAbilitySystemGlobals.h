

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "DGAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONS_API UDGAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
