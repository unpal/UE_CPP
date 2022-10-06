
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



};
