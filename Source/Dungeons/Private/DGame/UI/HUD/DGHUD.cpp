


#include "DGame/UI/HUD/DGHUD.h"
#include "DGame/UI/Widget/DGUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "DGame/UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* ADGHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerSubclass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void ADGHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetSubclass, TEXT("Overlay widget class unitialized, please fill out BP_DGHUD"));
	checkf(OverlayWidgetControllerSubclass, TEXT("Overlay Widget Controller Class IsActorInitialized(), please fill out BP_DGHUD"));
	
	OverlayWidget = CreateWidget<UDGUserWidget>(GetWorld(), OverlayWidgetSubclass);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController); 
	
	OverlayWidget->AddToViewport();
}
