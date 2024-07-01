#include "DGame/Player/DGPlayerState.h"

#include "DGame/AbilitySystem/DGAbilitySystemComponent.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"


ADGPlayerState::ADGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDGAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ADGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
