
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C01_Particle.generated.h"
UCLASS()
class UE_CPP_API AC01_Particle : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
public:	
	AC01_Particle();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
