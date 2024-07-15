

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DGAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController; 
class UOverlayWidgetController;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DUNGEONS_API UDGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="DGAbilitySystemLibrary|Character Class Defaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="DGAbilitySystemLibrary|Character Class Defaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category="DGAbilitySystemLibrary|Character Class Defaults")
	static  UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|Gameplay Effects")
	static bool IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|Gameplay Effects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintCallable, Category="DGAbilitySystemLibrary|Gameplay Effects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category="DGAbilitySystemLibrary|Gameplay Effects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category="DGAbilitySystemLibrary|Combat")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, float Radius, const FVector& SphereLocation, const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutOverlappingActors);

	UFUNCTION(BlueprintPure, Category="DGAbilitySystemLibrary|Fraction")
	static bool IsNotFriend(const AActor* FirstActor, const AActor* SecondActor);
};
