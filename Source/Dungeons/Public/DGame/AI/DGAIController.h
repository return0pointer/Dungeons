

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DGAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class DUNGEONS_API ADGAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADGAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
