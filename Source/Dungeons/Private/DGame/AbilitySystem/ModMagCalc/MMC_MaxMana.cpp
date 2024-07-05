


#include "DGame/AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "DGame/AbilitySystem/DGAttributeSet.h"
#include "DGame/Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntDef.AttributeToCapture = UDGAttributeSet::GetIntelligenceAttribute();
	IntDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(IntDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	constexpr float BaseValue = 50.f;
	constexpr float VigorMultiplier = 2.5f;
	constexpr float MpByLevel = 15.f;
	return BaseValue + VigorMultiplier * Vigor + MpByLevel * PlayerLevel;
}
