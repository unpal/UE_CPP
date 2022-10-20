#include "04_Particle/C01_Particle.h"
#include "Particles/ParticleSystemComponent.h"


AC01_Particle::AC01_Particle()
{
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	// ParticleSystemComponent �� �߰��մϴ�.
	
	// ����� Particle ������ �ε��մϴ�.
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'");
	if (particle.Succeeded())
	{
		// ParticleSystemComponent �� ����� Particle�� �����մϴ�.
		Particle->SetTemplate(particle.Object);
		// Particle �� �ڵ����� ������� �ʵ��� �����մϴ�.
		Particle->bAutoActivate = false;
	}
}

void AC01_Particle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC01_Particle::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Particle->ResetParticles(); // Particle �� �����մϴ�.
	Particle->SetActive(true); // Particle �� Ȱ��ȭ�մϴ�.

	FVector location = GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(EObjectTypeQuery::ObjectTypeQuery4); // �浹�� ������ �߰��մϴ�.

	TArray<AActor*> ignores; // �浹 �˻縦 ������ ���͸� ������ �迭

	TArray<FHitResult> hitResult; // �浹 �˻簡 �̷���� ���͸� ������ �迭

	// SphereTraceMultiForObjects : ���� �浹ü�� �Ͻ������� �����մϴ�.
	//								�浹�� ��ü�� �ִٸ� true ���ٸ� false �� ��ȯ�մϴ�.
	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects(
			 GetWorld(),	// SphereTrace �� ������ ����
			 location,   // ��������
			 location,   // ������
			 300,        // ������
			 types,      // �浹 �˻� ����
			 false,
			 ignores,    // �浹 �˻� ���� ���
			 DrawDebugType, // SphereTrace �׸��� ����
			 hitResult,     // �浹�� ���� ���
			 true);		   // �ڱ� �ڽ� �浹 ���� ���� 

	if (b) // �浹�� ��ü�� �����Ѵٸ�
	{
		// �浹�� ��ü�� ���Ͽ� ��� �ݺ��մϴ�.
		for (const FHitResult& hit : hitResult)
		{
			// �浹�� ������ RootComponent �� �����ɴϴ�.
			UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());

			// RootComponent �� UStaticMeshComponent �̸� �ش� ��ü�� ���� ��ü���
			// IsSimulatingPhysics : ������ü��� ture �ƴ϶�� false �� ��ȯ�մϴ�.
			if (mesh && mesh->IsSimulatingPhysics())
				mesh->AddRadialImpulse(
					location,	// ������ ��ġ
					1000,		// ������ ����
					50000.0f,  // ������ ���� ũ��
					ERadialImpulseFalloff::RIF_MAX); // ���� ������κ����� ���� ����
			// AddRadialImpulse : ����� ���ϴ� ���
		}
	}
}


