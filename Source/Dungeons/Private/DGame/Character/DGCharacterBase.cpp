#include "DGame/Character/DGCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "CharacterTrajectoryComponent.h"

ADGCharacterBase::ADGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterTrajectory = CreateDefaultSubobject<UCharacterTrajectoryComponent>("CharacterTrajectory");
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

UAbilitySystemComponent* ADGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADGCharacterBase::InitAbilityActorInfo()
{
}

void ADGCharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()))
	check(DefaultPrimaryAttributes)
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent()); 
}
