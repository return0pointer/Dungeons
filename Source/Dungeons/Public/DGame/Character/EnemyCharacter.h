#pragma once

#include "CoreMinimal.h"
#include "DGame/AbilitySystem/Data/CharacterClassInfo.h"
#include "DGame/Character/DGCharacterBase.h"
#include "DGame/Interaction/EnemyInterface.h"
#include "DGame/UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;

UCLASS()
class DUNGEONS_API AEnemyCharacter : public ADGCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	void SetupHealthBar();

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	virtual int32 GetPlayerLevel() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;

protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	
};
