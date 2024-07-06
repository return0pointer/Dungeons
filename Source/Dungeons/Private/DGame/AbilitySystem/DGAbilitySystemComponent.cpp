#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"

#include "DGame/AbilitySystem/Abilities/DGGameplayAbility.h"

void UDGAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDGAbilitySystemComponent::ClientEffectApplied);
}

void UDGAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UDGGameplayAbility* DgAbility = Cast<UDGGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(DgAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UDGAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UDGAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec); 			
		}
	}
}

void UDGAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                              const FGameplayEffectSpec& EffectSpec,
                                              FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnEffectAssetTags.Broadcast(TagContainer);
}
