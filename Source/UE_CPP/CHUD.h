
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class UE_CPP_API ACHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;
	bool bDraw = false;
	FLinearColor Color = FLinearColor::White;
public:
	ACHUD();
	virtual void DrawHUD() override;
	FORCEINLINE void Visible(){ bDraw = true; }
	FORCEINLINE void InVisible(){ bDraw = false;}
	
	FORCEINLINE void EnableTarget() { Color = FLinearColor::Red; }
	FORCEINLINE void DisableTarget() { Color = FLinearColor::White; }

};
