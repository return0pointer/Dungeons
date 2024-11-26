


#include "DGame/AbilitySystem/Data/AttributeInfo.h"

#include "Dungeons/DGLogChannels.h"

FDGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FDGAttributeInfo& Info : AttributeInfo)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogDG, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo[%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FDGAttributeInfo();
}
