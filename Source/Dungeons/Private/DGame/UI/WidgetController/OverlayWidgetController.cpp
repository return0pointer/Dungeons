#include "DGame/UI/WidgetController/OverlayWidgetController.h"

#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"

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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetHealthAttribute()).AddUObject(
		this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetMaxHealthAttribute()).AddUObject(
		this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetManaAttribute()).AddUObject(
		this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetMaxManaAttribute()).AddUObject(
		this, &UOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetStaminaAttribute()).AddUObject(
		this, &UOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DGAttributeSet->GetMaxStaminaAttribute()).AddUObject(
		this, &UOverlayWidgetController::MaxStaminaChanged);

	UDGAbilitySystemComponent* DgAbilitySystemComponent = Cast<UDGAbilitySystemComponent>(AbilitySystemComponent);
	DgAbilitySystemComponent->OnEffectAssetTags.AddLambda(
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

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}
