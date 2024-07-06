#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer&)

UCLASS()
class DUNGEONS_API UDGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTagsSignature OnEffectAssetTags;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag InputTag);
protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
