#include "DGame/Actor/DGEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "DGame/AbilitySystem/DGAttributeSet.h"

ADGEffectActor::ADGEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ADGEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UDGAttributeSet* DGAttributeSet = Cast<UDGAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UDGAttributeSet::StaticClass()));
		UDGAttributeSet* mutableAttSet = const_cast<UDGAttributeSet*>(DGAttributeSet);
		mutableAttSet->SetHealth(DGAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ADGEffectActor::OnEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
	}
}

void ADGEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADGEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADGEffectActor::OnEndOverlap);
}
