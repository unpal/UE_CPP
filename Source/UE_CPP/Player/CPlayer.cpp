#include "Player/CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"

#include "Camera/CameraComponent.h"


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
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",    this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",      this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook",   this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::Run);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released,this, &ACPlayer::Walk);

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

void ACPlayer::Run()
{
	// ĳ���� �̵��ӵ��� 600���� ����
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::Walk()
{
	// ĳ���� �̵��ӵ��� 400���� ����
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

