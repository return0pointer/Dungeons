

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DGHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UDGUserWidget;

struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class DUNGEONS_API ADGHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
		
	UPROPERTY()
	TObjectPtr<UDGUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDGUserWidget> OverlayWidgetSubclass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerSubclass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
