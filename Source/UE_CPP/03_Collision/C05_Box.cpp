#include "03_Collision/C05_Box.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h" 
// GameplayStatics.h : ���� �÷����� ���� ��Ȳ�� Ȯ���� �� �ִ� �Լ����� ���ִ� �����Դϴ�.

#include "C04_Trigger.h"

AC05_Box::AC05_Box()
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
	TextRender->Text = FText::FromString(FString("C05_Box"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");

	if (mesh.Succeeded())
	{
		for (int32 i = 0; i < 3; i++)
		{
			FString str;
			str.Append("Meshes");
			str.Append(FString::FromInt(i + 1));
			Meshes[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(str));
			Meshes[i]->SetupAttachment(Root);
			Meshes[i]->SetSimulatePhysics(true);
			Meshes[i]->SetRelativeLocation(FVector(250, i * 150, 250));
			Meshes[i]->SetStaticMesh(mesh.Object);
		}
	}
}

void AC05_Box::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors; // Actor �� ������ �迭�� �����մϴ�.

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AC04_Trigger::StaticClass(), actors);
	// UGameplayStatics::GetAllActorsOfClass(world, class, actorArray)
	// world �� �����ϴ� class �� �̷���� Actor ���� ã�� 
	// actorArray �� ��� �����մϴ�.

	AC04_Trigger* trigger = Cast<AC04_Trigger>(actors[0]);

	trigger->OnMultiBeginOverlap.AddUFunction(this, "OnPhysics");
	// AC04_Trigger �� �����ϴ� OnMultiBeginOverlap �븮�ڿ���
	// OnPysics ��� �Լ��� ��� ȣ���ϵ��� �߰��մϴ�.

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC05_Box::OnBeginOverlap);

	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'"));

	for (int i = 0; i < 3; ++i)
	{
		Materials[i] = UMaterialInstanceDynamic::Create(material, this);
		Meshes[i]->SetMaterial(0, Materials[i]);
		Meshes[i]->SetSimulatePhysics(false);

		FTransform transform = Meshes[i]->GetComponentToWorld();
		WorldLocations[i] = transform.GetLocation();
	}
}

void AC05_Box::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	OnPhysics(index, color);
}

void AC05_Box::OnPhysics(int32 index, FLinearColor color)
{
	for (int i = 0; i < 3; i++)
	{
		Materials[i]->SetVectorParameterValue("Color", FLinearColor(1, 1, 1));

		Meshes[i]->SetSimulatePhysics(false);
		Meshes[i]->SetWorldLocation(WorldLocations[i]);
	}

	Materials[index]->SetVectorParameterValue("Color", color);

	Meshes[index]->SetSimulatePhysics(true);
}