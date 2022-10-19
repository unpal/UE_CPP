

#include "07_TPS Folder/C_AnimNotifyState.h"
#include "IRifle.h"
FString UC_AnimNotifyState::GetNotifyName_Implementation() const
{ return "Equip";}

void UC_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Anim, TotalDuration);
	if (!MeshComp) return;
	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	if (!rifle) return;

	if(bUnqequip)
	{
		rifle->Begin_UnEquip_Rifle();
		return;
	}
	rifle->Begin_Equip_Rifle();
}

void UC_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp,UAnimSequenceBase* Anim)
{
	Super::NotifyEnd(MeshComp, Anim);
	if (!MeshComp) return;
	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	if (!rifle) return;

	if (bUnqequip)
	{
		rifle->End_UnEquip_Rifle();
		return;
	}
	rifle->End_Equip_Rifle();
}
