

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGUserWidget.generated.h"

UCLASS()
class DUNGEONS_API UDGUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
