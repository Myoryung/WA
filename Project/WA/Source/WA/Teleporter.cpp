// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "WA.h"
#include "WAViewportClient.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	SetActorEnableCollision(false);
}

void ATeleporter::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (puzzleActive && OtherActor->ActorHasTag(FName("Character")))
	{
		audioComp->Play();
		UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		UWASaveGame* WASaveGameInstance = Cast<UWASaveGame>(
			UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0));
		if (waInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save"));
			WASaveGameInstance->Save(FVector(0, 0, 0),
				3,
				1,
				waInstance->GetSaveSlotIndex(),
				waInstance->GetCurrentStage() +1);
		}
		if (GetWorld())
		{
			UWAViewportClient* waVP = Cast<UWAViewportClient>(GetWorld()->GetGameViewport());
			if (waVP)
			{
				waVP->Fade(1, true);
			}
		}
		waInstance->SetCurrentStage(waInstance->GetCurrentStage() + 1);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle,
			this, &ATeleporter::TransferLevel, 1.0f, true);
	}
}

void ATeleporter::OnSwitch()
{
	if (isTurnOn)
	{
		isTurnOn = false;
		SetActorEnableCollision(false);
	}
	else
	{
		isTurnOn = true;
		SetActorEnableCollision(true);
	}
	puzzleActive = isTurnOn;
}

void ATeleporter::TransferLevel()
{
	UGameplayStatics::OpenLevel(this, TransferLevelName);
}
