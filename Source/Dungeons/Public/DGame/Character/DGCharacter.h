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

	virtual void SetInvulnerability_Implementation(bool Invulnerability, bool ChangeVisibility) override;

	virtual UAnimMontage* GetJumpMontage_Implementation() override;
	
	virtual int32 GetPlayerLevel() override;

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Settings|Jump")
	UAnimMontage* JumpMontage;
};
