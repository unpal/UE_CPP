
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_PaticleTrigger.generated.h"

UCLASS()
class UE_CPP_API AC02_PaticleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AC02_PaticleTrigger();

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
};
