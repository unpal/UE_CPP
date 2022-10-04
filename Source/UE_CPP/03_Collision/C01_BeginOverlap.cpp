

#include "03_Collision/C01_BeginOverlap.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
AC01_BeginOverlap::AC01_BeginOverlap()
{ 
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(Root);
	// SetRelativeScale3D : ���輺 (�θ� �ڽİ��迡 ���ϴ�)�� �ִ� transform�� �����մϴ�.
	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
	//bHiddenInGame : �� ���ӿ����� ���ü� ���θ� ������ ���ִ� ����

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	// FRotator : roll , pitch , yaw ���� ������ ���ִ� ����
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	// TextRenderColor : �ؽ�Ʈ ���� ���� ����
	TextRender->Text = FText::FromString(FString("C01_BeginOverlap"));
	// Text : �ؽ�Ʈ ���� ����
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void AC01_BeginOverlap::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AC01_BeginOverlap::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC01_BeginOverlap::OnEndOverlap);
	// OnActorEndOverlap.AddDynamic(Object,Function)
	// ��ħ�� �������� �� ȣ���� �Լ��� �����մϴ�.
	//Object : ����� �Լ��� ������ �ִ� ��ü
}

void AC01_BeginOverlap::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str.Append("In : ");
	str.Append(OtherActor->GetName());

	TextRender->SetText(FText::FromString(str));
}

void AC01_BeginOverlap::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str.Append("Out : ");
	str.Append(OtherActor->GetName());
	// Append : str �ڿ� ���ڿ��� �ս��ϴ�.
	// GetName : ���� �ƿ����̳��� �̸��� �����ɴϴ�.
	TextRender->SetText(FText::FromString(str));
}

