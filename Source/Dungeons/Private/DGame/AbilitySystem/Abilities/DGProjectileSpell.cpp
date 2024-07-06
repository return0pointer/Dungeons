#include "DGame/AbilitySystem/Abilities/DGProjectileSpell.h"

#include "DGame/Actor/DGProjectile.h"
#include "DGame/Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

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
		DrawDebugSphere(GetOwningActorFromActorInfo()->GetWorld(), SocketLocation, 8, 8, FColor::Red, true, 20);
		DrawDebugSphere(GetOwningActorFromActorInfo()->GetWorld(), ProjectileTargetLocation, 8, 8, FColor::Blue, true, 20);
		DrawDebugLine(GetOwningActorFromActorInfo()->GetWorld(), SocketLocation, ProjectileTargetLocation, FColor::Green, true, 20);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		// TODO: Set the Projectile Rotation
		
		ADGProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADGProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
