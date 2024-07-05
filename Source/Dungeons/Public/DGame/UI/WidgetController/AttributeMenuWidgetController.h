

#pragma once

#include "CoreMinimal.h"
#include "DGame/UI/WidgetController/DGWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FDGAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FDGAttributeInfo&, info);


UCLASS(BlueprintType, Blueprintable)
class DUNGEONS_API UAttributeMenuWidgetController : public UDGWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValue() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;


protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:

	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
 