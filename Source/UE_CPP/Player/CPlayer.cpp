#include "Player/CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"

#include "Camera/CameraComponent.h"

#include "07_TPS Folder/C_Rifle.h"
#include "07_TPS Folder/C_UserWidget.h"

ACPlayer::ACPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	// Controller �� yaw ���� ������� �ʵ��� �����մϴ�.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Actor �� �̵��ϴ� ���� �������� ȸ���ϴ� ���� �����մϴ�.
	GetCharacterMovement()->MaxWalkSpeed = 400;
	// ĳ������ �̵��ӵ��� 400���� �����մϴ�.

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	if (mesh.Succeeded()) GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// FClassFinder : Class , Blueprint ������ ������ ã���ϴ�.
	// Object �� �ƴ� Class �� �����մϴ�.
	// �츮�� �߰��� ������ �ִϸ��̼��� �ƴ� �ִϸ��̼� �������Ʈ�̱�
	// ������ FClassFinder �������� ã�ƾ��մϴ�.
	ConstructorHelpers::FClassFinder<UAnimInstance> anim(L"AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'");
	if (anim.Succeeded()) GetMesh()->SetAnimClass(anim.Class);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	// SpringArm �� z ��ġ�� 60 ���� �����մϴ�.
	SpringArm->TargetArmLength = 200;
	// SpringArm �� ���̸� 200���� �����մϴ�.
	SpringArm->bUsePawnControlRotation = true;
	// SpringArm �� ��Ʈ�ѷ��� ȸ������ ����ϵ��� �մϴ�.
	SpringArm->SocketOffset = FVector(0, 60, 0);
	// SpringArm �� ���� ������ y ��ġ�� 60 ���� �����մϴ�.

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// �ش� ĳ���Ͱ� �÷��̾��� ���� �����մϴ�.
	JumpMaxCount = 2;
	GetCharacterMovement()->AirControl = 1;

	ConstructorHelpers::FClassFinder<UC_UserWidget> autofire(L"WidgetBlueprint'/Game/Blueprints/07_TPS/BP_UserWidget.BP_UserWidget_C'");
	if (autofire.Succeeded()) AutoFireClass = autofire.Class;

	 
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	AutoFire = CreateWidget<UC_UserWidget, APlayerController>(GetController<APlayerController>(), AutoFireClass);
	AutoFire->AddToViewport();

	Rifle = AC_RIfle::Spawn(GetWorld(), this);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",    this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",      this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook",   this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom",			 this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::Run);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released,this, &ACPlayer::Walk);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::StartJump);
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle_Equip);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);
	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPlayer::OnAutoFire);
}

void ACPlayer::OnMoveForward(float axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	// Controller �� yaw ȸ������ �����մϴ�.
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal();
	// Controller ������ �� ������ 1�� ����ȭ�� ������ �����մϴ�.

	AddMovementInput(direction, axis);
	// ĳ���͸� �������� �̵���ŵ�ϴ�.
}

void ACPlayer::OnMoveRight(float axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal();
	// Controller ������ ������ ������ 1�� ����ȭ�� ������ �����մϴ�.

	AddMovementInput(direction, axis);
}

void ACPlayer::OnHorizontalLook(float axis)
{ AddControllerYawInput(axis); }

void ACPlayer::OnVerticalLook(float axis)
{ AddControllerPitchInput(axis); }

void ACPlayer::OnZoom(float axis)
{
	SpringArm->TargetArmLength += (ZoomSpeed * axis * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength  = FMath::Clamp(SpringArm->TargetArmLength,ZoomRange.X,ZoomRange.Y);

}

void ACPlayer::Run()
{
	// ĳ���� �̵��ӵ��� 600���� ����
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::StartJump()
{
	bPressedJump = true;
}

void ACPlayer::EndJump()
{
	bPressedJump = false;
}

void ACPlayer::OnRifle_Equip()
{ Rifle->Equip(); }

void ACPlayer::OnAim()
{ Rifle->Begin_Aim(); }

void ACPlayer::OffAim()
{ Rifle->End_Aim(); }

void ACPlayer::OnFire()
{ Rifle->Begin_Fire(); }

void ACPlayer::OffFire()
{ Rifle->End_Fire(); }

void ACPlayer::OnAutoFire()
{
	Rifle->ToggleAutoFire();
	Rifle->GetAutoFire() ? AutoFire->On() : AutoFire->Off();
}

void ACPlayer::End_Equip_Rifle()
{
	Rifle->End_Equip();
}

void ACPlayer::Begin_UnEquip_Rifle()
{
	Rifle->Begin_UnEquip();
}

void ACPlayer::End_UnEquip_Rifle()
{
	Rifle->End_UnEquip();

}

bool ACPlayer::Get_Equip_Rifle()
{
    return false;
}

bool ACPlayer::Get_Aim_Rifle()
{
    return false;
}

void ACPlayer::Begin_Equip_Rifle()
{
	Rifle->Begin_Equip();
}

