#include "DGame/Character/DGCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "CharacterTrajectoryComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/CapsuleComponent.h"
#include "DGame/DGGameplayTags.h"
#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "Dungeons/Dungeons.h"
#include "Kismet/GameplayStatics.h"

ADGCharacterBase::ADGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterTrajectory = CreateDefaultSubobject<UCharacterTrajectoryComponent>("CharacterTrajectory");
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("UMotionWarping");
}

UAbilitySystemComponent* ADGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ADGCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

bool ADGCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* ADGCharacterBase::GetAvatar_Implementation()
{
	return this;
}

void ADGCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

TArray<FTaggedMontage> ADGCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* ADGCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage ADGCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage AttackMontage : AttackMontages)
	{
		if (AttackMontage.MontageTag == MontageTag)
		{
			return AttackMontage;
		}
	}
	return FTaggedMontage();
}

void ADGCharacterBase::MulticastHandleDeath_Implementation()
{
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetSimulatePhysics(false);
	Dissolve();
	bDead = true;
}


void ADGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector ADGCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageAttackTag)
{
	const FDGGameplayTags GameplayTags = FDGGameplayTags::Get();

	if (MeshSocketNames.Contains(MontageAttackTag))
	{
		const FName SocketName = *MeshSocketNames.Find(MontageAttackTag);
		return GetMesh()->GetSocketLocation(SocketName);
	}
	if (IsValid(Weapon) && WeaponSocketNames.Contains(MontageAttackTag))
	{
		const FName SocketName = *WeaponSocketNames.Find(MontageAttackTag);
		return Weapon->GetSocketLocation(SocketName);		
	}
	
	return FVector();	
}

void ADGCharacterBase::InitAbilityActorInfo() 
{
}

void ADGCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()))
	check(GameplayEffectClass)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent()); 
}

void ADGCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ADGCharacterBase::AddCharacterAbilities()
{
	UDGAbilitySystemComponent* DgASC = CastChecked<UDGAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	DgASC->AddCharacterAbilities(StartupAbilities);
}

void ADGCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterialInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);		
		GetMesh()->SetMaterial(0, DynamicMaterialInst);
		StartDissolveTimeline(DynamicMaterialInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterialInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);		
		Weapon->SetMaterial(0, DynamicMaterialInst);
		StartWeaponDissolveTimeline(DynamicMaterialInst);
	}
}

