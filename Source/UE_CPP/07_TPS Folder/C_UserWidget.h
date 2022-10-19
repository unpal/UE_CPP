
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UserWidget.generated.h"

UCLASS()
class UE_CPP_API UC_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void On();
	UFUNCTION(BlueprintImplementableEvent)
	void Off();

};
