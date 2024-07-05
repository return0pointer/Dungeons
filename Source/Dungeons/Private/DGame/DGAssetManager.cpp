


#include "DGame/DGAssetManager.h"

#include "DGame/DGGameplayTags.h"

UDGAssetManager& UDGAssetManager::Get()
{
	check(GEngine);
	
	UDGAssetManager* DGAssetManager = Cast<UDGAssetManager>(GEngine->AssetManager);
	return *DGAssetManager;
}

void UDGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FDGGameplayTags::Get().InitializeNativeGameplayTags();
}