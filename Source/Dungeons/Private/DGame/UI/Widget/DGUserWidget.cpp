#include "DGame/UI/Widget/DGUserWidget.h"

void UDGUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
