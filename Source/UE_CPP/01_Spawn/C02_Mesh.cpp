#include "01_Spawn/C02_Mesh.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AC02_Mesh::AC02_Mesh()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
}

void AC02_Mesh::BeginPlay()
{
	Super::BeginPlay();
	
	UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, L"MaterialInstanceConstant'/Game/Mesh/M_BasicShape_Inst.M_BasicShape_Inst'");
	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	Material = UMaterialInstanceDynamic::Create(material, this);

	Mesh->SetMaterial(0, Material);


	// ��������
	// ����� �Լ��������� ��밡���� ����
	// 
	// �ɹ�����
	// �ش� Ŭ���� �ȿ��� ����� ������ Ŭ������ �Լ����� ��� ������ �����մϴ�.

	// Timer : �ֱ������� ������ ����� �����ϴ� ���
	// K2_SetTimer(Ÿ�̸� ������, ȣ���� �Լ� �̸�, ������ �ֱ�, �ݺ����࿩��);
	// ȣ���� �Լ��� UFUNCTION  ���� ������ �Լ����� �մϴ�.
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
}

void AC02_Mesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC02_Mesh::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	Material->SetVectorParameterValue("Color", color);
}


