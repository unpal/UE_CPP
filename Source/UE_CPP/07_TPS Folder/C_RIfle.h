
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_RIfle.generated.h"

UCLASS()
class UE_CPP_API AC_RIfle : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_RIfle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void zooming(float Output);
	static AC_RIfle* Spawn(class UWorld* InWorld, class ACharater* InOwner);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* GrapMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* UnGrapMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		class UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		float AimDistane = 3000;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UMatineeCameraShake> CameraShake;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class USoundCue* MuzzleSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* FlashParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class AC_Bullet> BulletClass;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UMaterialInstanceConstant* ImpactDecal;
	
	
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	class ACharacter* Owner;

	bool bEquipped;
	bool bEquipping;
	bool bAimming;
	bool bFiring;
	bool bAutoFiring;
	
	FTimeline Timeline;
	FOnTimelineFloat  OnTimelineFloat;

	float PitchAngle;
	
	FTimerHandle AutoFireHandle;
	

	void Firing();

public:
	void Equip();
	void Begin_Equip();
	void End_Equip();

	void UnEquip();
	void Begin_UnEquip();
	void End_UnEquip();

	void Begin_Aim();
	void End_Aim();

	void Begin_Fire();
	void End_Fire();

	void ToggleAutoFire();

private:
	bool IsAvalibaleAim();

public:
	FORCEINLINE bool GetEquipped() { return bEquipped; }
	FORCEINLINE bool GetAiming() { return bAimming; }
	FORCEINLINE bool GetAutoFire() { return bAutoFiring; }
};
