#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "07_TPS/IRifle.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_CPP_API ACPlayer : public ACharacter, public IIRifle
{
	// ACharacter  
	// SkeltealMeshComponent : ���� �޽� ���
	// ArrowComponent : ���� ���
	// CharacterMovementComponent : ������ ���
	// Pawn : �Է¹��� �� �ִ� Actor
	// CapsuleComponent : Capsule ������ �浹ü
	// �� �⺻������ ������ �ִ� Ŭ�����Դϴ�.

	GENERATED_BODY()

private :
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UC_UserWidget> AutoFireClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float ZoomSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		FVector2D ZoomRange = FVector2D(0, 500);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	// Camera �� �繰�� �����Ͽ� �÷��̾ �Կ��� �� 
	// �ֵ��� SpringArmComponent �� �߰��մϴ�.

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
	// Player �� ������ �� �ֵ��� Camera �� �߰��մϴ�.

private :
	class AC_Rifle* Rifle;
	class UC_UserWidget* AutoFire;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	void OnMoveForward(float axis);	// �� �� �̵�
	void OnMoveRight(float axis);   // �� �� �̵�

	void OnHorizontalLook(float axis); 
	void OnVerticalLook(float axis);

	void OnZoom(float axis);

	void Run();
	void Walk();

	void OnRifle_Equip();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();

	void OnAutoFire();

private :
	virtual void Begin_Equip_Rifle()   override;
	virtual void End_Equip_Rifle()     override;
	virtual void Begin_UnEquip_Rifle() override;
	virtual void End_UnEquip_Rifle()   override;
	virtual bool Get_Equip_Rifle()     override;
	virtual bool Get_Aim_Rifle()       override;
};
