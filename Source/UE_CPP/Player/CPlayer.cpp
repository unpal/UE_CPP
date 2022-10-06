

#include "Player/CPlayer.h"
#include "GameFramework/SpringarmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"

#include "Camera/CameraComponent.h"
ACPlayer::ACPlayer()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera = CreateAbstractDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	bUseControllerRotationYaw = false;
	// Controller의 Yaw 값을 사용하지 않도록 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Actor 가 이동하는 방향 기준으로 회전하는 것을 설정
	GetCharacterMovement()->MaxWalkSpeed = 400;
	// 캐릭터의 이동속도를 400으로 설정
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	if (mesh.Succeeded()) GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	// FClassFinder : class , blueprint 형식을 찾아줍니다
	ConstructorHelpers::FClassFinder<UAnimInstance> anim(L"AnimBlueprint'/Game/Blueprints/Player/ABP_Player.ABP_Player_C'");
	if (anim.Succeeded()) GetMesh()->SetAnimClass(anim.Class);
	
	
	
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	// SpringArm 의 z 위치를 60으로 설정합니다.
	SpringArm->TargetArmLength = 200;
	// SpringArm 의 길이를 200으로 설정
	SpringArm->bUsePawnControlRotation = true;
	// SpringArm이 컨트롤러의 회전값을 사용하도록 설정합니다
	SpringArm->SocketOffset = FVector(0, 0, 60);
	// SpringArm 의 시작지점의 y위치를 60 으로 설정합니다

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}



void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("verticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Run",EInputEvent::IE_Pressed, this, &ACPlayer::Run);
	PlayerInputComponent->BindAction("Run",EInputEvent::IE_Released, this, &ACPlayer::Walk);
}

void ACPlayer::OnMoveForward(float axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	// Controller 의 Yaw 회전값을 저장합니다
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal();
	// Controller 기준의 앞 방향을 1로 정규화된 값으로 저장합니다.

	AddMovementInput(direction, axis);
}

void ACPlayer::OnMoveRight(float axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal();
	// Controller 기준의 오른쪽 방향을 1로 정규화된 값으로 저장합니다.
	AddMovementInput(direction, axis);
}

void ACPlayer::OnHorizontalLook(float axis)
{	AddControllerYawInput(axis);	}

void ACPlayer::OnVerticalLook(float axis)
{	AddControllerPitchInput(axis);	}

void ACPlayer::Run()
{
	//이동속도 600
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::Walk()
{
	//이동속도 400
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

