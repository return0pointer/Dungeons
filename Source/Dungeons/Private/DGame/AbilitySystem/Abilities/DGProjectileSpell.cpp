#include "DGame/AbilitySystem/Abilities/DGProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "DGame/DGGameplayTags.h"
#include "DGame/Actor/DGProjectile.h"
#include "DGame/Interaction/CombatInterface.h"

void UDGProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
}

void UDGProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		AActor* Owner = GetOwningActorFromActorInfo();
		DrawDebugSphere(Owner->GetWorld(), SocketLocation, 8, 8, FColor::Red, true, 20);
		DrawDebugSphere(Owner->GetWorld(), ProjectileTargetLocation, 8, 8, FColor::Blue, true, 20);
		DrawDebugLine(Owner->GetWorld(), SocketLocation, ProjectileTargetLocation, FColor::Green, true, 20);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		ADGProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADGProjectile>(
			ProjectileClass,
			SpawnTransform,
			Owner,
			Cast<APawn>(Owner),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->SetOwnerAvatar(GetAvatarActorFromActorInfo());

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		const FDGGameplayTags GameplayTags = FDGGameplayTags::Get();
		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage);
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
