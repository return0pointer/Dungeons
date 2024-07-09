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
	void SetupBinding();

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpanAfterDie;
	
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

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
