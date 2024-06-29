#include "DGame/Character/DGCharacterBase.h"
#include "CharacterTrajectoryComponent.h"

ADGCharacterBase::ADGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterTrajectory = CreateDefaultSubobject<UCharacterTrajectoryComponent>("CharacterTrajectory");
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void ADGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}