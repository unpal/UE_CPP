
#include "06_Sound/C02_Sound3D.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GamePlayStatics.h"
#include "../Player/CPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
AC02_Sound3D::AC02_Sound3D()
{
		PrimaryActorTick.bCanEverTick = true;
		Root = CreateDefaultSubobject<USceneComponent>("Root");
		SetRootComponent(Root);
		Box = CreateDefaultSubobject<UBoxComponent>("Box");
		Box->SetupAttachment(Root);
		TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
		TextRender->SetupAttachment(Root);

		Box->SetRelativeScale3D(FVector(3));
		Box->bHiddenInGame = false;

		TextRender->SetRelativeLocation(FVector(0, 0, 100));
		TextRender->SetRelativeRotation(FRotator(0));
		TextRender->SetRelativeScale3D(FVector(2));
		TextRender->TextRenderColor = FColor::Black;
		TextRender->Text = FText::FromString(FString("C02_Sound3D"));
		TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

		ConstructorHelpers::FObjectFinder<USoundCue> sound(L"SoundCue'/Game/Sounds/S_Stepdirt_Cue.S_Stepdirt_Cue'");
		if (sound.Succeeded()) Sound = sound.Object;


	}

void AC02_Sound3D::BeginPlay()
	{
		Super::BeginPlay();
		OnActorBeginOverlap.AddDynamic(this, &AC02_Sound3D::OnBeginOverlap);
	}

	void AC02_Sound3D::OnBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
	{
		if (OtherActor != Cast<ACPlayer>(OtherActor)) return;

		if (bStop)
		{
			bStop = false;
			UKismetSystemLibrary::K2_SetTimer(this, "Play", 0.5f, true);
		}

		else
		{
			bStop = true;
			UKismetSystemLibrary::K2_ClearTimer(this, "Play");
		}
	}

	void AC02_Sound3D::Play()
	{
		if (USoundAttenuation)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 1, 1, 0, USoundAttenuation);
	}



