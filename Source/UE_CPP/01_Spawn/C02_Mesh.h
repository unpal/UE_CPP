#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Mesh.generated.h"

UCLASS()
class UE_CPP_API AC02_Mesh : public AActor
{
	GENERATED_BODY()
	
private :
	// Mesh : ����
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	// UStaticMeshComponent 
	// �ش� Ŭ�������� Mesh ����� �߰��� �� �ֽ��ϴ�.

	class UMaterialInstanceDynamic* Material;

public:	
	AC02_Mesh();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION : �����Ϳ��� ������ �Լ���� ���� ����ϴ� Ű����
	UFUNCTION()
	void ChangeColor();
};
