#pragma once

#include "CoreMinimal.h"
#include "DGame/Character/DGCharacterBase.h"
#include "DGame/Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DUNGEONS_API AEnemyCharacter : public ADGCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	virtual int32 GetPlayerLevel() override;

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
