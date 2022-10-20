#include "UE_CPPGameModeBase.h"
#include "GameFramework/HUD.h"

AUE_CPPGameModeBase::AUE_CPPGameModeBase()
{
    // ������ �⺻ ĳ���͸� �����մϴ�.
    ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/Player/BP_Player.BP_Player_C'");
    if (pawn.Succeeded()) DefaultPawnClass = pawn.Class;

    // ������ �⺻ HUD �� �����մϴ�.
    ConstructorHelpers::FClassFinder<AHUD> hud(L"Blueprint'/Game/BP_HUD.BP_HUD_C'");
    if (hud.Succeeded()) HUDClass = hud.Class;
}