#include "Player/PlayerAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "07_TPS Folder/IRifle.h"
void UPlayerAnim::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Owner = Cast<ACharacter>(TryGetPawnOwner());
}

void UPlayerAnim::NativeUpdateAnimation(float DelatSeconds)
{
    Super::NativeUpdateAnimation(DelatSeconds);

    if (!Owner) return;

    // GetVelocity() : ¼Ó·Â
    Speed = Owner->GetVelocity().Size2D();
    Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetControlRotation());
	IsInAir = Owner->GetCharacterMovement()->IsFalling();

	IIRifle* rifle = Cast<IIRifle>(Owner);
	if(rifle)
	{
		bEquipped = rifle->Get_Equip_Rifle();
		bAiming = rifle->Get_Aim_Rifle();
	}
	Pitch = Owner->GetBaseAimRotation().Pitch;
}
