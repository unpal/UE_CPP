
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"
UCLASS()
class UE_CPP_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animetion")
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animetion")
		float Direction;
private:
	class ACharacter* Owner;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DelatSeonds) override;

};
