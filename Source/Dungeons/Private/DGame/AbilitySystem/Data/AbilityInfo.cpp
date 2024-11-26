


#include "DGame/AbilitySystem/Data/AbilityInfo.h"

#include "Dungeons/DGLogChannels.h"

FDGAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FDGAbilityInfo& Info : AbilityInfos)
	{
		if (Info.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogDG, Error, TEXT("Can't find Info for AbilityTag [%s] on AbilityInfo[%s]."), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	
	return FDGAbilityInfo();
}
