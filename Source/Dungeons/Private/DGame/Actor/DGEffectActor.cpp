#include "DGame/Actor/DGEffectActor.h"

#include "Components/SphereComponent.h"

ADGEffectActor::ADGEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ADGEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ADGEffectActor::OnEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ADGEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADGEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADGEffectActor::OnEndOverlap);
}


