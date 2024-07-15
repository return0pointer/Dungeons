#include "DGame/AbilitySystem/DGAbilitySystemLibrary.h"

#include "DGame/DGAbilityTypes.h"
#include "DGame/DGGameMode.h"
#include "DGame/Interaction/CombatInterface.h"
#include "DGame/Player/DGPlayerState.h"
#include "DGame/UI/HUD/DGHUD.h"
#include "DGame/UI/WidgetController/DGWidgetController.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UDGAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADGHUD* DgHUD = Cast<ADGHUD>(PC->GetHUD()))
		{
			ADGPlayerState* PS = PC->GetPlayerState<ADGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DgHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UDGAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADGHUD* DgHUD = Cast<ADGHUD>(PC->GetHUD()))
		{
			ADGPlayerState* PS = PC->GetPlayerState<ADGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DgHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UDGAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
                                                          ECharacterClass CharacterClass, float Level,
                                                          UAbilitySystemComponent* ASC)
{
	const AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UDGAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
                                                   ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;

	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->CharacterClassInformation[CharacterClass];
	for (const TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.CommonAbilities)
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		if (CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UDGAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const ADGGameMode* GM = Cast<ADGGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GM == nullptr) return nullptr;

	return GM->CharacterClassInfo;
}

bool UDGAbilitySystemLibrary::IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDGGameplayEffectContext* DGEffectContext = static_cast<const FDGGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return DGEffectContext->IsBlockedHit();
	}
	return false;
}

bool UDGAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDGGameplayEffectContext* DGEffectContext = static_cast<const FDGGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return DGEffectContext->IsCriticalHit();
	}
	return false;
}

void UDGAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FDGGameplayEffectContext* DGEffectContext = static_cast<FDGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DGEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UDGAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FDGGameplayEffectContext* DGEffectContext = static_cast<FDGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DGEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UDGAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, float Radius,
                                                         const FVector& SphereLocation,
                                                         const TArray<AActor*>& ActorsToIgnore,
                                                         TArray<AActor*>& OutOverlappingActors)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereLocation, FQuat::Identity,
		                                FCollisionObjectQueryParams(
			                                FCollisionObjectQueryParams::InitType::AllDynamicObjects),
		                                FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap :Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}						
		}
	}
}

bool UDGAbilitySystemLibrary::IsNotFriend(const AActor* FirstActor, const AActor* SecondActor)
{
	const bool FirstIsPlayer = FirstActor->ActorHasTag(FName("Player"));
	const bool SecondIsPlayer = SecondActor->ActorHasTag(FName("Player"));
	const bool FirstIsEnemy = FirstActor->ActorHasTag(FName("Enemy"));
	const bool SecondIsEnemy = SecondActor->ActorHasTag(FName("Enemy"));

	const bool BothArePlayers = FirstIsPlayer && SecondIsPlayer;
	const bool BothAreEnemies = FirstIsEnemy && SecondIsEnemy;
	const bool Friends = BothAreEnemies || BothArePlayers;
	return !Friends;
}
