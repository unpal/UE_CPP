
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Trigger.generated.h"

UCLASS()
class UE_CPP_API AC04_Trigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AC04_Trigger();

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Meshes[3];
	UPROPERTY(VisibleDefaultsOnly)
		class  USpotLightComponent* SpotLights[3];
	class UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocations[3]; // �ʱ⿡ �����Ǿ� �ִ� ���ڵ��� ��ġ�� ���� ����
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	void OnPhysics(int32 index, FLinearColor color);

	void OnLight(int32 index, FLinearColor color);
};
