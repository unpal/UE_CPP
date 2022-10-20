#include "07_TPS/C_Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"


AC_Bullet::AC_Bullet()
{
	Capsule    = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Mesh       = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");

	Capsule->SetRelativeRotation(FRotator(90, 0, 0)); 
	Capsule->SetCapsuleHalfHeight(50);
	Capsule->SetCapsuleRadius(2);
	Capsule->SetCollisionProfileName("BlockAllDynamic");
	// Overlap �� �ƴ� ������ �� Hit �浹�� �����ϵ��� �����մϴ�.

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Sphere.SM_Sphere'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> material(L"MaterialInstanceConstant'/Game/Materials/M_Bullet_Inst.M_Bullet_Inst'");
	if (material.Succeeded()) Mesh->SetMaterial(0, material.Object);

	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeScale3D(FVector(1, 0.025f, 0.025f));
	Mesh->SetRelativeRotation(FRotator(90, 0, 0));

	Projectile->InitialSpeed = 2e+4f; // ó�� ����ü �ӵ�
	Projectile->MaxSpeed = 2e+4f;     // ����ü �ְ� �ӵ�
	Projectile->ProjectileGravityScale = 0; // �߷°�
}

void AC_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	// Capsule �� ������ �浹�� �Ͼ�ٸ� OnHit �Լ��� �����մϴ�.
	Capsule->OnComponentHit.AddDynamic(this, &AC_Bullet::OnHit);
}

void AC_Bullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	Destroy(); // �ش� ��ü�� �ı��մϴ�.
}

void AC_Bullet::Shoot(const FVector& InDirection)
{
	// Velocity : �������� ���ư��� �ӷ�
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
	// ����ü�� Velocity �� InDirection �� �������� �ʱ� �ӷ� ��ŭ ���ư����� �����մϴ�.
}

