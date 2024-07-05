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
}

UAbilitySystemComponent* ADGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADGPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
