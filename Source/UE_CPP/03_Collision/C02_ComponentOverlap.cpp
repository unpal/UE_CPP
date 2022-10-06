

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
	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	TextRender->Text = FText::FromString(FString("C01_BeginOverlap"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(Root);
	PointLight->SetLightColor(FLinearColor::Red);
	
}

void AC02_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();
	PointLight->SetVisibility(false);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnEndOverlap);
}

void AC02_ComponentOverlap::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	PointLight->SetVisibility(true);

}

void AC02_ComponentOverlap::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetVisibility(false);
	FLinearColor Color;
	PointLight->SetLightColor(FLinearColor(UKismetMathLibrary::RandomFloatInRange(0, 1), UKismetMathLibrary::RandomFloatInRange(0, 1), UKismetMathLibrary::RandomFloatInRange(0, 1)));
}

