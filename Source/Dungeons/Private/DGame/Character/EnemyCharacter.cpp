


#include "DGame/Character/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AEnemyCharacter::HighlightActor()
{
	bHighlighted = true;
}

void AEnemyCharacter::UnHighlightActor()
{
	bHighlighted = false;
}
