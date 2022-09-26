#pragma once

#include "CoreMinimal.h"
// CoreMinimal : Engine ���� ����� �� �ִ� �⺻ ��ɵ��� ��Ƴ��� ���
#include "GameFramework/Actor.h"
// Actor : ���忡 ��ġ�� �� �ִ� ����� ��Ƴ��� ����
#include "C01_Spawn.generated.h"
// generated : ���ø�����Ʈ�� �����Ϳ��� �ش� ������ �ִٴ� ���� �˷��ִ� ����
/*
class template : cpp �� h �� ���� �̸����� �����

.h : ��������� ������ �ۼ�, ���е�� �� ���ִ� �ൿ �̸� �ۼ�
Haeder File : �̸� ������� ��ɵ��� ��Ƴ��� ���Ϸ� #include �� �߰��ϰ�
			  �ȴٸ� �ش� ���Ͽ��� ��ɵ��� ����� �� �ֽ��ϴ�.
.cpp : �ൿ���� ��ü���� ����� �ۼ�
*/
// UCLASS : Unreal �� ����� �� �ִ� class ��� ���� ���
UCLASS()
class UE_CPP_API AC01_Spawn : public AActor
{
	GENERATED_BODY()
		// GENERATED_BODY()
		// �ش� ��ġ���� class �� ��ü��� ���� �ǹ��մϴ�.
private:
	/*
	UPROPERTY() : Reflection ����� ����� �� �ִ� Ű�����Դϴ�.
				  UPROPERTY �� ��õ��� ���� �������� �����Ϳ��� �������� �ʽ��ϴ�.

	Unreal ������ ������ Ÿ���� �����մϴ�.
	1. c++ Ÿ�� : c++ �� �̷���� �ڵ带 ���մϴ�.
	2. ��Ű Ÿ�� : c++ �ڵ带 ���̽��� ������� �������Ʈ�� ���մϴ�.
	3. �ν��Ͻ� Ÿ�� : ��Ű Ÿ������ ���忡 ��ġ�Ǿ� �ִ� �������� ������ ���մϴ�.
	EditAnywhere : ��ŰŸ��, �ν��Ͻ�Ÿ�� ��� �����Ͽ� ������ �����մϴ�.
	EditInstanceOnly : ��ŰŸ�Կ��� �����ϸ� ��ŰŸ�Կ��� ������ �����մϴ�.
	EditDefaultsOnly : �ν��Ͻ� Ÿ�Կ��� �����ϸ� �ν��Ͻ� Ÿ�Կ��� ������ �����մϴ�.
	VisibleAnywhere : ��ŰŸ�԰� �ν��Ͻ�Ÿ�� ��� ���������� ������ �Ұ����մϴ�.
	*/
	UPROPERTY(EditAnywhere)
		int A = 10;
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	UPROPERTY(EditDefaultsOnly)
		int C = 30;
	UPROPERTY(VisibleAnywhere)
		int D = 40;

	/*
	Actor �� ����� ���� Variable �̶�� Ŭ������ �����ϰ�
	�ɹ� ���� Var1,Var2,Var3,Var4 �����آa

	Var1 �� ��Ű, �ν��Ͻ� �� �����ϰ� ���� �ȉ�

	Var2 �� ��Ű ���� ���� ����

	Var3 �� ��Ű �ν��Ͻ� ���� ���� ����

	Var4 �ν��Ͻ� ���� ���� ����
	*/
public:	
	AC01_Spawn();
	//������(Constructor) :	��ü�� ������ �� ȣ���ϴ� �Լ��Դϴ�.
	//						Ŭ���� ��� ���� �̸��� �Լ��Դϴ�.
	//��ü(object) :			��� ������ �̷���� ����Ʈ����� ��ü�ϴ� �޸�

protected:
	//BeginPlay() : ������ ���۵� �� �� �ѹ� ȣ��Ǵ� �Լ�
	virtual void BeginPlay() override;


public:	
	// Tick() : ���� ���� �� �� �����Ӹ��� ȣ��Ǵ� �Լ��Դϴ�.
	virtual void Tick(float DeltaTime) override;
	
};
