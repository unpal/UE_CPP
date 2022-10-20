#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Sound2D.generated.h"

UCLASS()
class UE_CPP_API AC01_Sound2D : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	UPROPERTY(VisibleDefaultsOnly)
		class USoundCue* Sound; // USoundCue : �����Դϴ�.

private :
	class UAudioComponent* Audio;
	// UAudioComponent : ���带 ����� �� �ִ� ����Դϴ�.

public:	
	AC01_Sound2D();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
