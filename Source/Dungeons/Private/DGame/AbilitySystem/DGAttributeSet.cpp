


#include "DGame/AbilitySystem/DGAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDGAttributeSet::UDGAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(150.f);
	InitMana(50.f);
	InitMaxMana(80.f);
	InitStamina(120.f);
	InitMaxStamina(100.f);
}

void UDGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UDGAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDGAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDGAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDGAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDGAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UDGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDGAttributeSet, Health, OldHealth);
}

void UDGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDGAttributeSet, MaxHealth, OldMaxHealth);
}

void UDGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDGAttributeSet, Mana, OldMana);
}

void UDGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDGAttributeSet, MaxMana, OldMaxMana);
}

void UDGAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDGAttributeSet, Stamina, OldStamina);
}

void UDGAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDGAttributeSet, MaxStamina, OldMaxStamina);
}
