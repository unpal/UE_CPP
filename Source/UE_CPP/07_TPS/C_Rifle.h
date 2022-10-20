#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_Rifle.generated.h"

UCLASS()
class UE_CPP_API AC_Rifle : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket    = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* GrabMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* UnGrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		class UCurveFloat* Curve; // ���� ��ȯ �ӵ�

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float AimDistance = 3000; // ����ü�� �Ÿ�

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UMatineeCameraShake> CameraShake; // �� ī�޶� ȿ��

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class USoundCue* MuzzleSoundCue; // �� ����

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* FlashParticle; // �Һ� ��ƼŬ

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* EjectParticle; // ���� ��ƼŬ

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class AC_Bullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* ImpactParticle; // Ÿ�� ��ƼŬ

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UMaterialInstanceConstant* ImpactDecal; // ���� ���� �浹�� ��� �߻��� ��Į

private :
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private :
	class ACharacter* Owner; // �����ϰ� �ִ� ĳ����

	bool bEquipped;   // ������ ���� ����
	bool bEquipping;  // �����߿� ���� ����
	bool bAiming;     // ���� ���¿� ���� ����
	bool bFiring;     // �� ����
	bool bAutoFiring; // ����, �ܹ� ����

	FTimeline Timeline;
	FOnTimelineFloat OnTimelineFloat;

	float PitchAngle; // ���� ��� ����

	FTimerHandle AutoFireHandle;

public:	
	AC_Rifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public :
	static AC_Rifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public :
	UFUNCTION()
		void Zooming(float Output);

private :
	void Firing(); // �� ���

public :
	// ����
	void       Equip();
	void Begin_Equip();
	void   End_Equip();

	// ��������
	void   UnEquip();
	void Begin_UnEquip();
	void   End_UnEquip();

	// ����
	void Begin_Aim();
	void   End_Aim();

	// ��
	void Begin_Fire();
	void   End_Fire();

	// ���� , �ܹ�
	void ToggleAutoFire();

private :
	bool IsAvalibaleAim(); // ���� ���� ����

public :
	FORCEINLINE bool GetEquipped() { return bEquipped;   }
	FORCEINLINE bool GetAiming()   { return bAiming;    }
	FORCEINLINE bool GetAutoFire() { return bAutoFiring; }
};
