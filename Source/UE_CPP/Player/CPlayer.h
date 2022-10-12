#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_CPP_API ACPlayer : public ACharacter
{
	// ACharacter  
	// SkeltealMeshComponent : ���� �޽� ���
	// ArrowComponent : ���� ���
	// CharacterMovementComponent : ������ ���
	// Pawn : �Է¹��� �� �ִ� Actor
	// CapsuleComponent : Capsule ������ �浹ü
	// �� �⺻������ ������ �ִ� Ŭ�����Դϴ�.

	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	// Camera �� �繰�� �����Ͽ� �÷��̾ �Կ��� �� 
	// �ֵ��� SpringArmComponent �� �߰��մϴ�.

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
	// Player �� ������ �� �ֵ��� Camera �� �߰��մϴ�.

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

	void Run();
	void Walk();
};
