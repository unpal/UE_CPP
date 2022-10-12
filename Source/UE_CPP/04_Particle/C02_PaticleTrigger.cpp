

#include "04_Particle/C02_PaticleTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "C01_Particle.h"
#include "Kismet/GamePlayStatics.h"
AC02_PaticleTrigger::AC02_PaticleTrigger()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(Root);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	TextRender->Text = FText::FromString(FString("C02_ParticleTrigger"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

}

void AC02_PaticleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC01_Particle::StaticClass(), actors);
	AC01_Particle* particle = Cast<AC01_Particle>(actors[0]);
		OnActorBeginOverlap.AddDynamic(particle, &AC01_Particle::ActorBeginOverlap);
}		



