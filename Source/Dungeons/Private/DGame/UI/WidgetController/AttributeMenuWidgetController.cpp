


#include "DGame/UI/WidgetController/AttributeMenuWidgetController.h"

#include "DGame/DGGameplayTags.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"
#include "DGame/AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UDGAttributeSet* AS = CastChecked<UDGAttributeSet>(AttributeSet);	
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
		);
	}
	
}

void UAttributeMenuWidgetController::BroadcastInitialValue()
{
	UDGAttributeSet* AS = CastChecked<UDGAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FDGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
