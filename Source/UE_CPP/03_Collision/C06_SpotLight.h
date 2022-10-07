
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C06_SpotLight.generated.h"

UCLASS()
class UE_CPP_API AC06_SpotLight : public AActor
{
	GENERATED_BODY()
	
public:	
	AC06_SpotLight();

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
	FVector WorldLocations[3]; // �ʱ⿡ �����Ǿ� �ִ� ���ڵ��� ��ġ�� ���� ����
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	void OnLight(int32 index, FLinearColor color);

};
