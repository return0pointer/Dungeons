

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGCharacterBase.generated.h"

class UCharacterTrajectoryComponent;

UCLASS(Abstract)
class DUNGEONS_API ADGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADGCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<UCharacterTrajectoryComponent> CharacterTrajectory;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
