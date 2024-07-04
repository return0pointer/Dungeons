#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DGAbilitySystemComponent.generated.h"

UCLASS()
class DUNGEONS_API UDGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
