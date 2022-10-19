

#include "CHUD.h"
#include "Engine/Canvas.h"
ACHUD::ACHUD()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> texture(L"Texture2D'/Game/Textures/T_Dot.T_Dot'");
	if (texture.Succeeded()) Texture = texture.Object;

}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!bDraw) return;

	FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D size(Texture->GetSizeX() * 0.5f, Texture->GetSizeY() * 0.5f);
	FVector2D position = center - size;

	FCanvasTileItem item(position, Texture->Resource, Color);

	Canvas->DrawItem(item);
}
