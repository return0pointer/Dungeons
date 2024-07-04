

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DGCharacterBase.generated.h"

class UCharacterTrajectoryComponent;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class DUNGEONS_API ADGCharacterBase : public ACharacter, public IAbilitySystemInterface
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
};
