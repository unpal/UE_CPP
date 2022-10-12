#include "03_Collision/C02_ComponentOverlap.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"

AC02_ComponentOverlap::AC02_ComponentOverlap()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(Root);
	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(Root);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	TextRender->Text = FText::FromString(FString("C02_ComponentOverlap"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	PointLight->SetLightColor(FLinearColor::Red);
	// ����Ʈ ����Ʈ�� ���� ������ ���������� �����մϴ�.
}

void AC02_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();
	
	PointLight->SetVisibility(false);
	// ����Ʈ ����Ʈ�� ���ü� ���θ� �����մϴ�.

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnEndOverlap);
}

void AC02_ComponentOverlap::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLight->SetVisibility(true);
}

void AC02_ComponentOverlap::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;
	PointLight->SetLightColor(color);
	PointLight->SetVisibility(false);
}


