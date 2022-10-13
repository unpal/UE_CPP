
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Teleport.generated.h"

UCLASS()
class UE_CPP_API AC03_Teleport : public AActor
{
	GENERATED_BODY()
	
public:	
	AC03_Teleport();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(EditInstanceOnly)
		class UTextRenderComponent* TextRender;
	UPROPERTY(EditInstanceOnly)
		FVector TeleportLocation;
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
