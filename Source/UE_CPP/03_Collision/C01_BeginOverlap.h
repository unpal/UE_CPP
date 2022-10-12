#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_BeginOverlap.generated.h"

UCLASS()
class UE_CPP_API AC01_BeginOverlap : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	// BoxComponent : Box ������ ���
	//                Collision ��ɿ��� ����մϴ�.
	// Collision : �浹ü�� ���ϸ� ��� ���Ͱ� �浹�ߴ� ���� �˻��ϴ� ���
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	// SceneComponent : �����ִ� ����� �ֻ� �θ��Դϴ�.
	// Root : SceneComponent �� ������
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	// TextRenderComponent : �ؽ�Ʈ�� �׷��ִ� ���

public:	
	AC01_BeginOverlap();

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
		void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
