#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DGAbilitySystemComponent.generated.h"

class UDGAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer&)
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGivenSignature, UDGAbilitySystemComponent*)
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&)

UCLASS()
class DUNGEONS_API UDGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTagsSignature OnEffectAssetTags;
	FAbilitiesGivenSignature AbilitiesGivenDelegate;
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
	bool bStartupAbilitiesGive = false;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag InputTag);
	
	void ForEachAbility(const FForEachAbility& Delegate);
	
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
protected:
	
	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
