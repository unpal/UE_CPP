#include "05_LineTrace/C01_LineTrace.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "../Player/CPlayer.h"
#include "C02_Cylinder.h"


AC01_LineTrace::AC01_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	TextRender->Text = FText::FromString(FString("C01_LineTrace"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void AC01_LineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC02_Cylinder::StaticClass(), actors);

	// ã�� AC02_Cylinder ���� ��ŭ �ݺ��մϴ�.
	for (AActor* actor : actors)
	{
		// ���ҵ��� AC02_Cylinder �� ��ȯ�ϰ�
		AC02_Cylinder* obj = Cast<AC02_Cylinder>(actor);
		IgnoreActors.Add(actor);
		if (obj) Cylinders.Add(obj);
		// ��ȯ�� �����Ǿ��ٸ� Cylinders �� �߰��մϴ�.
	}
}

void AC01_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	for (AC02_Cylinder* elem : Cylinders)
	{
		FVector start = elem->GetActorLocation();
		FVector end   = elem->GetActorLocation();

		end.Z += 100;

		FHitResult hitResult;

		bool b = UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, IgnoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true);
		
		if (b) StartJump(hitResult.GetActor());
	}
}

void AC01_LineTrace::StartJump(AActor* InActor)
{
	ACPlayer* player = Cast<ACPlayer>(InActor);
	if (player)
		player->LaunchCharacter(FVector(0, 0, 700), true, true);
}

