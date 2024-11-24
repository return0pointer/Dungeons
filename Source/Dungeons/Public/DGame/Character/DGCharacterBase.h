

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DGame/Interaction/CombatInterface.h"
#include "DGCharacterBase.generated.h"

class UNiagaraSystem;
class UGameplayAbility;
class UGameplayEffect;
class UCharacterTrajectoryComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UAnimMontage;

UCLASS(Abstract)
class DUNGEONS_API ADGCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ADGCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<UCharacterTrajectoryComponent> CharacterTrajectory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionWarping")
	class UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// Combat Interface
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;	
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageAttackTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;	
	virtual void Die() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	// end Combat Interface

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	
	
protected:
	virtual void BeginPlay() override;
	
	bool bDead = false;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const;
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	// Dissolve effects

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="_Settings|Combat|Material")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="_Settings|Combat|Material")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
	
	// Settings

	// Sockets
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|Combat|Socket")
	TMap<FGameplayTag, FName> MeshSocketNames;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|Combat|Socket")
	TMap<FGameplayTag, FName> WeaponSocketNames;

	// GAS
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	// Effects
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="_Settings|Combat|Effects")
	UNiagaraSystem* BloodEffect;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="_Settings|Combat|Effects")
	USoundBase* DeathSound;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|Combat|Montage")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "_Settings|Combat|Attack")
	TArray<FTaggedMontage> AttackMontages;

	// Minions

	int32 MinionCount = 0;
	
};
