#include "DGame/UI/WidgetController/OverlayWidgetController.h"

#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"
#include "DGame/AbilitySystem/Data/AbilityInfo.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	Super::BroadcastInitialValue();

	const UDGAttributeSet* DGAttributeSet = CastChecked<UDGAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(DGAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DGAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(DGAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(DGAttributeSet->GetMaxMana());
	OnStaminaChanged.Broadcast(DGAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(DGAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	const UDGAttributeSet* DGAttributeSet = CastChecked<UDGAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
		);
	
	if (UDGAbilitySystemComponent* DgASC = Cast<UDGAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (DgASC->bStartupAbilitiesGive)
		{
			OnInitializeStartupAbilities(DgASC);
		}
		else
		{
			DgASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
						
		DgASC->OnEffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{				
				FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(GameplayTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);					
				}
			}
		}
		);
	}
	
	
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UDGAbilitySystemComponent* DgAbilitySystemComponent)
{	
	if (!DgAbilitySystemComponent->bStartupAbilitiesGive) return;
	
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, DgAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		FDGAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(DgAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = DgAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	DgAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

