

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


USTRUCT(BlueprintType)
struct FDGAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 
 */
UCLASS()
class DUNGEONS_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FDGAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDGAttributeInfo> AttributeInfo;
};
