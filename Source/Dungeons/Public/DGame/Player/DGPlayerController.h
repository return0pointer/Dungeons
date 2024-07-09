#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "GameplayTagContainer.h"
#include "DGPlayerController.generated.h"

class UDamageTextComponent;
class UDGInputConfig;
class IEnemyInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UDGAbilitySystemComponent;
class USplineComponent;

UCLASS()
class DUNGEONS_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADGPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	FHitResult& GetCursorHit() { return CursorHit; }

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DGContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AimingAction;

	void Move(const FInputActionValue& InputActionValue);
	void AimingPressed() { bAimingKeyDown = true; }
	void AimingReleased() { bAimingKeyDown = false; }
	bool bAimingKeyDown;
	
	void CursorTrace();

	TObjectPtr<IEnemyInterface> LastActor;
	TObjectPtr<IEnemyInterface> ThisActor;
	FHitResult CursorHit;


	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UDGInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UDGAbilitySystemComponent> DGAbilitySystemComponent;

	UDGAbilitySystemComponent* GetASC();

	FVector CachedDestination;
	float FollowTime;
	float ShortPressThreshold;
	bool bAutoRunning;
	bool bTargeting;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
	void AutoRun();

	UPROPERTY(EditDefaultsOnly, Category="_Setting|Widget")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
