#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_AnimNotifyState.generated.h"

UCLASS()
class UE_CPP_API UC_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditAnywhere)
		bool bUnqequip; // ���������� ������������ ���� ����

private :
	// Editor ���� ���� NotifyName �� �����մϴ�.
	FString GetNotifyName_Implementation() const override; 

	// Notify �� ���� �� �� ����� �߰��մϴ�.
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim, float TotalDuration) override;

	// Notify �� ���� �� ����� �߰��մϴ�.
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim) override;
};
