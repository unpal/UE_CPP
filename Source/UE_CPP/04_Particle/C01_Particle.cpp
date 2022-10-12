

#include "04_Particle/C01_Particle.h"
#include "Particles/ParticleSystemComponent.h"
AC01_Particle::AC01_Particle()
{
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'");
	if(particle.Succeeded())
	{
		Particle->SetTemplate(particle.Object);
		Particle->bAutoActivate = false;
	}
}

void AC01_Particle::BeginPlay()
{
	Super::BeginPlay();
}

void AC01_Particle::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
		Particle->ResetParticles();
		Particle->SetActive(true);

		FVector location = GetActorLocation();

		TArray<TEnumAsByte<EObjectTypeQuery>> types;
		types.Add(EObjectTypeQuery::ObjectTypeQuery4); // �浹�� ������ ����

		TArray<AActor*> ignores;

		TArray<FHitResult> hitResult;
		//SphereTraceMultiForObjects : ���� �浹ü�� �Ͻ������� ����
		//							 : �浹�� ��ü�� �ִٸ� true ���ٸ� false ��ȯ
		bool b = UKismetSystemLibrary::SphereTraceMultiForObjects(
			GetWorld(), // ������ ����
			location, //��������
			location, // ������
			300, // ������
			types,// �浹 �˻� ����
			false, 
			ignores, // �浹 �˻� ���� ���
			DrawDebugType, // �׸��� ����
			hitResult, // �浹�� ���� ���
			true);  // �ڱ� �ڽ� �浹 ����
if(b)
{
	for(const FHitResult& hit : hitResult)
	{
		// �浹�� ������ RootComponent�� �����ɴϴ�
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());
		// RootComponent�� UstaticComponent�̸� �ش� ��ü�� ���� ��ü���
		// IsSimulatingPhysics : ���� ��ü��� true �ƴ϶�� flase ��ȯ
		if (mesh && mesh->IsSimulatingPhysics())
			mesh->AddRadialImpulse(
				location,  // ������ ��ġ
				1000, // ������ ����
				100000.0f, // ������ ���� ũ��
				ERadialImpulseFalloff::RIF_MAX); // ���� ������κ����� ���� ����
		//AddRadialImpulse : ����� ���ϴ� ���

	}
}
}


