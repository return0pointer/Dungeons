


#include "DGame/AbilitySystem/DGAbilitySystemGlobals.h"

#include "DGame/DGAbilityTypes.h"

FGameplayEffectContext* UDGAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FDGGameplayEffectContext();
}
