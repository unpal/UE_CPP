#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UCLASS()
class UE_CPP_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;
	// BlueprintReadOnly : Blueprint ���� ���� �� ������
	//					   ������ �Ұ����ϵ��� �����մϴ�.

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		bool bAiming;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Pitch;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		bool bEquipped;
private :
	class ACharacter* Owner;
public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DelatSeconds) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsInAir;
};
