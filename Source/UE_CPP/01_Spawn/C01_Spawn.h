#pragma once

#include "CoreMinimal.h"
// CoreMinimal : Engine ���� ����� �� �ִ� �⺻ ��ɵ��� ��Ƴ��� ����
#include "GameFramework/Actor.h"
// Actor : ���忡 ��ġ�� �� �ִ� ����� ��Ƴ��� ����
#include "C01_Spawn.generated.h"
// generated : ���ø�����Ʈ�� �����Ϳ��� �ش� ���� �ִٴ� ���� �˷��ִ� ����

/*
class template : cpp �� h �� ���� �̸����� �����

.h : ��������� ������ �ۼ� , ���е�� �� �� �ִ� �ൿ�� �̸� �ۼ�
Header File : �̸� ������� ��ɵ��� ��Ƴ��� ���Ϸ� #include �� �߰��ϰ�
              �ȴٸ� �ش� ���Ͽ��� ��ɵ��� ����� �� �ֽ��ϴ�.

.cpp : �ൿ���� ��ü���� ����� �ۼ�
*/

// UCLASS() : Unreal �� ����� �� �ִ� class ��� ���� ���
UCLASS()
class UE_CPP_API AC01_Spawn : public AActor
{
	GENERATED_BODY()
	// GENERATED_BODY()
	// �ش� ��ġ���� class �� ��ü��� ���� ����մϴ�.
	
private :
	/*
	UPROPERTY() : Reflection ����� ����� �� �ִ� Ű�����Դϴ�.
				  UPROPERTY �� ��õ��� ���� �������� �����Ϳ��� �������� �ʽ��ϴ�.
	
	Unreal ������ ������ Ÿ���� �����մϴ�.
	1. C++ Ÿ�� : C++ �� �̷���� �ڵ带 ���մϴ�.
	2. ��Ű Ÿ�� : C++ �ڵ带 ���̽��� ������� �������Ʈ�� ���մϴ�.
	3. �ν��Ͻ� Ÿ�� : ��Ű Ÿ������ ���忡 ��ġ�Ǿ� �ִ� ���纻�� ���մϴ�.
	
	EditAnywhere : ��ŰŸ�� , �ν��Ͻ�Ÿ�Կ��� ��� �����ϸ� ������ �����մϴ�.
	EditInstanceOnly : �ν��Ͻ�Ÿ�Կ����� �����ϸ� ������ �����մϴ�.
	EditDefaultsOnly : ��ŰŸ�Կ����� �����ϸ� ������ �����մϴ�.
	VisibleAnywhere : ��ŰŸ�� , �ν��Ͻ�Ÿ�Կ��� ��� �����ϸ� ������ �Ұ����մϴ�.
	*/

	UPROPERTY(EditAnywhere)
		int A = 10;
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	UPROPERTY(EditDefaultsOnly)
		int C = 30;
	UPROPERTY(VisibleAnywhere)
		int D = 40;

	int E = 50;

public:	
	AC01_Spawn();
	/* 
	������(Constructor) : ��ü�� ������ �� �� �ѹ� ȣ���ϴ� �Լ��Դϴ�.
						  Ŭ������� ���� �̸��� �Լ��Դϴ�.

	��ü(Object) : ��� ������ �̷���� ����Ʈ����� ��ü�ϴ� �޸�
	*/
protected:
	// BeginPlay() : ������ ���۵� �� �� �ѹ� ȣ���ϴ� �Լ��Դϴ�.
	virtual void BeginPlay() override;

public:	
	// Tick() : ���� ���� �� �� �����Ӹ��� ȣ���ϴ� �Լ��Դϴ�.
	virtual void Tick(float DeltaTime) override;
};
