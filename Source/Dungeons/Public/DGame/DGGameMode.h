#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DGGameMode.generated.h"

class UCharacterClassInfo;

UCLASS()
class DUNGEONS_API ADGGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
	
};
