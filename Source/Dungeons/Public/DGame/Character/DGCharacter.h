#pragma once

#include "CoreMinimal.h"
#include "DGame/Character/DGCharacterBase.h"
#include "DGCharacter.generated.h"

UCLASS()
class DUNGEONS_API ADGCharacter : public ADGCharacterBase
{
	GENERATED_BODY()

public:
	ADGCharacter();	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	class USpringArmComponent* SpringArmComponent;

protected:
	virtual void InitAbilityActorInfo() override;
};
