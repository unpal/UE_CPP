#include "01_Spawn/C01_Spawn.h"

AC01_Spawn::AC01_Spawn()
{
	// Tick �Լ� ���� ��� �ٸ� �Լ��ʹ� �ٸ���
	// �� �����Ӹ��� ȣ��Ǳ� ������ ����� ��Դϴ�.
	// bCanEverTick �� Tick �Լ��� ��뿩�θ� �����մϴ�.
	PrimaryActorTick.bCanEverTick = true;
}

void AC01_Spawn::BeginPlay()
{
	// Super : ��ӹ��� Ŭ������ �Լ��� ��������ִ� ����Դϴ�.
	Super::BeginPlay();
	
}

void AC01_Spawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// DeltaTime : ������ ������ ���� �ð��� ������

	// ������ : �ʴ� ȭ���� ���� �ֱ� �ӵ�
}