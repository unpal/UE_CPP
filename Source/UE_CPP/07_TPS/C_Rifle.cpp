#include "07_TPS/C_Rifle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Gameframework/Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Gameframework/PlayerController.h"
#include "Gameframework/SpringArmComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"

#include "Animation/AnimMontage.h"

#include "Camera/CameraComponent.h"

#include "Sound/SoundCue.h"

#include "Particles/ParticleSystemComponent.h"

#include "Materials/MaterialInstanceConstant.h"

#include "C_Bullet.h"
#include "CHUD.h"


AC_Rifle::AC_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabMontage(L"AnimMontage'/Game/Character/Animations/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (grabMontage.Succeeded()) GrabMontage = grabMontage.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> unGrabMontage(L"AnimMontage'/Game/Character/Animations/Rifle/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	if (unGrabMontage.Succeeded()) UnGrabMontage = unGrabMontage.Object;

	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(L"CurveFloat'/Game/Blueprints/07_TPS/Curve_Aim.Curve_Aim'");
	if (curve.Succeeded()) Curve = curve.Object;

	ConstructorHelpers::FObjectFinder<USoundCue> sound(L"SoundCue'/Game/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	if (sound.Succeeded()) MuzzleSoundCue = sound.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> flash(L"ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	if (flash.Succeeded()) FlashParticle = flash.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> eject(L"ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	if (eject.Succeeded()) EjectParticle = eject.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> impact(L"ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	if (impact.Succeeded()) ImpactParticle = impact.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> decal(L"MaterialInstanceConstant'/Game/Materials/M_Decal_Inst.M_Decal_Inst'");
	if (decal.Succeeded()) ImpactDecal = decal.Object;

	ConstructorHelpers::FClassFinder<UMatineeCameraShake> cameraShake(L"Blueprint'/Game/Blueprints/07_TPS/BP_CameraShake.BP_CameraShake_C'");
	if (cameraShake.Succeeded()) CameraShake = cameraShake.Class;

	ConstructorHelpers::FClassFinder<AC_Bullet> bullet(L"Blueprint'/Game/Blueprints/07_TPS/BP_Bullet.BP_Bullet_C'");
	if (bullet.Succeeded()) BulletClass = bullet.Class;
}

void AC_Rifle::BeginPlay()
{
	Super::BeginPlay();
	
	// �����ָ� �����մϴ�.
	Owner = Cast<ACharacter>(GetOwner());
	// �������� �޽��� HolsterSocket �� �ش� ���͸� 
	// ��� Ʈ�������� ������ ä �����մϴ�.
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	OnTimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, OnTimelineFloat);
	Timeline.SetPlayRate(200);
}

void AC_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
	if (!bAiming) return;

	UCameraComponent* Camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));

	FVector dircetion = Camera->GetForwardVector();

	FTransform transform = Camera->GetComponentToWorld();
	FVector start = transform.GetLocation() + dircetion;

	FVector end = transform.GetLocation() + dircetion * AimDistance;

	ACHUD* hud = Owner->GetController<APlayerController>()->GetHUD<ACHUD>();

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(Owner);

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery3,
		false, ignoreActors, EDrawDebugTrace::None, hitResult, true);

	if (hitResult.bBlockingHit)
		hud->EnableTarget();
	else
		hud->DisableTarget();
}

AC_Rifle* AC_Rifle::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params; // ���� ������ ���� �Ű����� ����Դϴ�.
	params.Owner = InOwner; // �Ű������� ���� InOwner �� �����ַ� �����մϴ�.

	// �Ű������� ���� InWorld �� AC_Rifle �� �����ϰ� �ּҰ��� ��ȯ�մϴ�.
	return InWorld->SpawnActor<AC_Rifle>(params);
}

void AC_Rifle::Zooming(float Output)
{
	UCameraComponent* Camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));
	Camera->FieldOfView = Output;
}

void AC_Rifle::Firing()
{
	FVector direction, start, end;
	//ī�޶� ����ũ
	if(IsAvalibaleAim())
	{
		UCameraComponent* Camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));

		direction = Camera->GetForwardVector();

		FTransform transform = Camera->GetComponentToWorld();
		start = transform.GetLocation() + direction;

		 end = transform.GetLocation() + direction * AimDistance;
		
		 direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(direction, 0.2f);
		 APlayerController* controller = Owner->GetController<APlayerController>();
		 if (CameraShake) controller->PlayerCameraManager->StartCameraShake(CameraShake);
	}
	//����
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	
	{
		if (MuzzleSoundCue)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), MuzzleSoundCue,muzzleLocation);

	}
	//��ƼŬ
	{
		if (FlashParticle)
			UGameplayStatics::SpawnEmitterAttached
			(FlashParticle, Mesh, "MuzzleFlash",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::KeepRelativeOffset);
		if(EjectParticle)
			UGameplayStatics::SpawnEmitterAttached
			(EjectParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);


	}
	//�ҷ�����
	if(BulletClass)
	{
		FVector spawnLocation = muzzleLocation + direction * 100;
		AC_Bullet* bullet = GetWorld()->SpawnActor<AC_Bullet>(BulletClass, spawnLocation, direction.Rotation());
		bullet->Shoot(direction);

	}
	//�浹ó��
	PitchAngle -= 0.25f * GetWorld()->DeltaTimeSeconds;
	Owner->AddControllerPitchInput(PitchAngle);
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(Owner);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery3,
		false, ignoreActors, EDrawDebugTrace::None, hitResult, true);
	if(hitResult.bBlockingHit)
	{
		FRotator rotator = hitResult.ImpactNormal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, rotator);

		UDecalComponent* decal = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(), ImpactDecal, FVector(5), hitResult.Location, rotator, 10);
		decal->SetFadeScreenSize(0);

		UStaticMeshComponent* mesh =
			Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
		if (mesh && mesh->BodyInstance.bSimulatePhysics)
		{
			direction = hitResult.GetActor()->GetActorLocation() -
				Owner->GetActorLocation();

			direction.Normalize();

			mesh->AddImpulseAtLocation(
				direction * 300 * mesh->GetMass(), Owner->GetActorLocation());
		}
	}
}

bool AC_Rifle::IsAvalibaleAim()
{
	USpringArmComponent* SpringArm = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));
	UCameraComponent* Camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));
	APlayerController* Controller = Owner->GetController<APlayerController>();
	return SpringArm && Camera && Controller;
}

void AC_Rifle::Equip()
{
	// �����ϰ� �ִ� �����̶�� �Լ��� �����մϴ�.
	if (bEquipping) return;

	// �����ϴ� �ִ� �����̶�� üũ�մϴ�.
	bEquipping = true;
	
	// �������� ���¿��ٸ�
	if (bEquipped == true)
	{
		// ���� ������ �����մϴ�.
		UnEquip();
		return;
	}

	// GrabMontage �� 2�� �ӵ��� ����մϴ�.
	Owner->PlayAnimMontage(GrabMontage, 2);
}

void AC_Rifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(Owner->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket);
}

void AC_Rifle::End_Equip()
{ bEquipping = false; }

void AC_Rifle::UnEquip()
{
	Owner->PlayAnimMontage(UnGrabMontage, 2);
}

void AC_Rifle::Begin_UnEquip()
{
	AttachToComponent(Owner->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket);
	bEquipped = false;
}

void AC_Rifle::End_UnEquip()
{
	bEquipping = false;
}

void AC_Rifle::Begin_Aim()
{
	if (!bEquipped) return;
	if (bEquipping) return;
	if (!IsAvalibaleAim()) return;
	bAiming = true;
	Owner->bUseControllerRotationYaw = true;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
	USpringArmComponent* SpringArm = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));

	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	Timeline.PlayFromStart();
	Owner->GetController<APlayerController>()->GetHUD<ACHUD>()->Visible();
}

void AC_Rifle::End_Aim()
{
	if (!bAiming) return;
	bAiming = false;
	Owner->bUseControllerRotationYaw = false;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	USpringArmComponent* SpringArm = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 20, 0);


	Timeline.ReverseFromEnd();
	Owner->GetController<APlayerController>()->GetHUD<ACHUD>()->InVisible();
}

void AC_Rifle::Begin_Fire()
{
	if (!bEquipped) return;
	if (bEquipping) return;
	if (!bAiming)  return;
	if (bFiring) return;

	bFiring = true;
	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this, &AC_Rifle::Firing, 0.1, true, 0);

		return;
	}

	Firing();

}

void AC_Rifle::End_Fire()
{
	bFiring = false;

	if (bAutoFiring)
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
}

void AC_Rifle::ToggleAutoFire()
{
	if (!bFiring) bAutoFiring = !bAutoFiring;
}
