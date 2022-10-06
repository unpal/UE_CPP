#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_Box.generated.h"

UCLASS()
class UE_CPP_API AC05_Box : public AActor
{
	GENERATED_BODY()
	
public:	
	AC05_Box();

protected:
	virtual void BeginPlay() override;


};
