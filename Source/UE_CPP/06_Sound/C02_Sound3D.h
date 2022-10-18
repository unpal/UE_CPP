
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Sound3D.generated.h"

UCLASS()
class UE_CPP_API AC02_Sound3D : public AActor
{
	GENERATED_BODY()
	
public:	
	AC02_Sound3D();

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight;
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	class UAudioComponent* Audio;
	// UAudioComponent : 사운드 재생 가능한 컴포넌트
	UPROPERTY(VisibleDefaultsOnly)
		class USoundCue* Sound;
	UPROPERTY(EditAnywhere)
		class USoundAttenuation* USoundAttenuation;
	bool bStop;
	UFUNCTION()
		void Play();
};
