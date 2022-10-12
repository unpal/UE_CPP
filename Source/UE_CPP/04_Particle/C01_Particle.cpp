

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
		types.Add(EObjectTypeQuery::ObjectTypeQuery4); // 충돌할 유형을 결정

		TArray<AActor*> ignores;

		TArray<FHitResult> hitResult;
		//SphereTraceMultiForObjects : 원형 충돌체를 일시적으로 생성
		//							 : 충돌한 물체가 있다면 true 없다면 false 반환
		bool b = UKismetSystemLibrary::SphereTraceMultiForObjects(
			GetWorld(), // 실행할 월드
			location, //시작지점
			location, // 끝지점
			300, // 반지름
			types,// 충돌 검사 유형
			false, 
			ignores, // 충돌 검사 제외 목록
			DrawDebugType, // 그리기 설정
			hitResult, // 충돌된 액터 목록
			true);  // 자기 자신 충돌 여부
if(b)
{
	for(const FHitResult& hit : hitResult)
	{
		// 충돌된 액터의 RootComponent를 가져옵니다
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());
		// RootComponent가 UstaticComponent이며 해당 객체가 물리 객체라면
		// IsSimulatingPhysics : 물리 객체라면 true 아니라면 flase 반환
		if (mesh && mesh->IsSimulatingPhysics())
			mesh->AddRadialImpulse(
				location,  // 폭발할 위치
				1000, // 폭발할 범위
				100000.0f, // 폭발할 힘의 크기
				ERadialImpulseFalloff::RIF_MAX); // 폭발 기원으로부터의 강도 세기
		//AddRadialImpulse : 충격을 가하는 기능

	}
}
}


