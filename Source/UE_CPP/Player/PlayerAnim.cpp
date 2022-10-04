

#include "Player/PlayerAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
void UPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnim::NativeUpdateAnimation(float DelatSeonds)
{
	Super::NativeUpdateAnimation(DelatSeonds);

	if (!Owner) return;
	
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetControlRotation());
}
