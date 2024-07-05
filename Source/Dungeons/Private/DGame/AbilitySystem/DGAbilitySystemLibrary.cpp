


#include "DGame/AbilitySystem/DGAbilitySystemLibrary.h"

#include "DGame/Player/DGPlayerState.h"
#include "DGame/UI/HUD/DGHUD.h"
#include "DGame/UI/WidgetController/DGWidgetController.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UDGAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADGHUD* DgHUD = Cast<ADGHUD>(PC->GetHUD()))
		{
			ADGPlayerState* PS = PC->GetPlayerState<ADGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DgHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UDGAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADGHUD* DgHUD = Cast<ADGHUD>(PC->GetHUD()))
		{
			ADGPlayerState* PS = PC->GetPlayerState<ADGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DgHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
