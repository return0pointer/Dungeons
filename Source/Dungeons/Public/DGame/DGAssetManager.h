

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONS_API UDGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UDGAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
