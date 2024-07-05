

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DGame/Interaction/CombatInterface.h"
#include "DGCharacterBase.generated.h"

class UGameplayEffect;
class UCharacterTrajectoryComponent;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class DUNGEONS_API ADGCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ADGCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<UCharacterTrajectoryComponent> CharacterTrajectory;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const;
	void InitializeDefaultAttributes() const;
};
