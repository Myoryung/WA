// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WAGameModeBase.h"
#include "WASaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Components/BillboardComponent.h"
#include "Door.h"
#include "Runtime/Engine//Public/EngineUtils.h"

AWAGameModeBase::AWAGameModeBase()
{
	CurrentRoomNum = 1;
}

void AWAGameModeBase::Init()
{
	UWorld* world = GetWorld();

	if (world)
	{
		//GameLoad
		auto WASaveGame = Cast<UWASaveGame>(UGameplayStatics::LoadGameFromSlot(saveSlotName, 0));
		if (WASaveGame)
		{
			// Ÿ��Ʋ ȭ�鿡�� ������ ��������
		}
		//Init room data and Disable not current room
		for (const auto& entity : FActorRange(world))
		{
			if (entity->GetName().Contains(TEXT("Room")))
			{
				rooms.Add(entity);
			}
		}
		for (int i = 0; i < rooms.Num(); i++)
		{
			for (int j = 0; j < rooms.Num(); j++)
			{
				if (rooms[j]->GetName() ==
					FString("Room" + FString::FromInt(i + 1)))
				{
					rooms.Swap(i, j);
					break;
				}
			}
			if (i != CurrentRoomNum - 1)
				DisableActor(rooms[i]);
		}
		for (TActorIterator<ADoor> iter(GetWorld()); iter; ++iter)
		{
			if (iter->GetName() ==
				FString("Gate" + FString::FromInt(CurrentRoomNum) +
					"_1"))
			{
				respawnPoint = iter->FindComponentByClass<UBillboardComponent>()
					->GetComponentLocation();
				break;
			}
		}
		maxRoomNumber = rooms.Num();
	}
}

void AWAGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AWAGameModeBase::AddInitPuzzle(ADefaultPuzzle* value, int roomNum){
	InitPuzzles.Add(roomNum, value);
}

void AWAGameModeBase::RoomReset(){
	for (TMultiMap<int8, ADefaultPuzzle*>::TKeyIterator iter = InitPuzzles.CreateKeyIterator(CurrentRoomNum);
		iter; ++iter)
		iter.Value()->InitializePuzzle();
}

void AWAGameModeBase::SetRespawnPoint(FVector point)
{
	respawnPoint = point;
}

void AWAGameModeBase::ChangeRoom(int8 roomNum, FVector resPoint)
{
	if ((roomNum > 0 || roomNum < maxRoomNumber)
		|| (CurrentRoomNum > 0 || CurrentRoomNum < maxRoomNumber))
	{
		EnableActor(rooms[roomNum - 1]);
		DisableActor(rooms[CurrentRoomNum - 1]);
	}
	CurrentRoomNum = roomNum;
	respawnPoint = resPoint;
}

void AWAGameModeBase::SetCurrentRoomNum(int8 value)
{
	CurrentRoomNum = value;
}

void AWAGameModeBase::DisableActor(AActor * target)
{
	TArray<AActor*> children;
	target->GetAttachedActors(children);
	if (children.Num() > 0)
	{
		for (int i = 0; i < children.Num(); i++)
		{
			DisableActor(children[i]);
		}
	}
	if (!target->IsHidden())
		target->SetActorHiddenInGame(true);
	if (target->GetActorEnableCollision())
		target->SetActorEnableCollision(false);
}

void AWAGameModeBase::EnableActor(AActor * target)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *(target)->GetName());
	TArray<AActor*> children;
	target->GetAttachedActors(children);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), children.Num());
	if (children.Num() > 0)
	{
		for (int i = 0; i < children.Num(); i++)
		{
			EnableActor(children[i]);
		}
	}
	if (target->IsHidden())
		target->SetActorHiddenInGame(false);
	if (!target->GetActorEnableCollision())
		target->SetActorEnableCollision(true);

}

FVector AWAGameModeBase::GetRespawnPoint() const
{
	return respawnPoint;
}
