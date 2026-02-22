#include "DGame/Player/DGPlayerState.h"

#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"
#include "Net/UnrealNetwork.h"


ADGPlayerState::ADGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDGAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void ADGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADGPlayerState, Level);
	DOREPLIFETIME(ADGPlayerState, XP);
}

UAbilitySystemComponent* ADGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADGPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void ADGPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void ADGPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void ADGPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void ADGPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void ADGPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}
