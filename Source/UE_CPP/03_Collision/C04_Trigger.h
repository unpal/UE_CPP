#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Trigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiBeginOverlapSignature, int32, FLinearColor);

UCLASS()
class UE_CPP_API AC04_Trigger : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Meshes[3];

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];

public:	
	AC04_Trigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

private :
	// �ڽ����� ������ ��ȯ�ϰ� �����ϵ����ϴ� �Լ�
	void OnPhysics(int32 index, FLinearColor color); 

	// ����Ʈ ����Ʈ�� ������ ��ȯ�ϴ� �Լ�
	void OnLight(int32 index, FLinearColor color);

private :
	class UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocations[3];	// �ʱ⿡ �����Ǿ� �ִ� ���ڵ��� ��ġ�� ���� ����

public :
	FMultiBeginOverlapSignature OnMultiBeginOverlap;
};
