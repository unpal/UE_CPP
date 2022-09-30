#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class UE_CPP_API AC03_Spawner : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AActor> SpawnClass;
	// TSubclassOf<expression>
	// expression ���¸� ��ӹް� �ִ� ��� Ŭ���� ������
	// ����ټ� �ִ� ����Դϴ�.

public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

};
