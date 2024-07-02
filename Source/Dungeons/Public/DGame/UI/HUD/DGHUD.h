

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DGHUD.generated.h"

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
		
	UPROPERTY()
	TObjectPtr<UDGUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDGUserWidget> OverlayWidgetSubclass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerSubclass;
};
