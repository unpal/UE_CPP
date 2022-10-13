
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Cylinder.generated.h"

UCLASS()
class UE_CPP_API AC02_Cylinder : public AActor
{
	GENERATED_BODY()
	
public:	
	AC02_Cylinder();

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

};
