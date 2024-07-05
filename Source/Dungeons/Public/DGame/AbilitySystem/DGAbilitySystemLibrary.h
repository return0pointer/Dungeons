

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DGAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class DUNGEONS_API UDGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
