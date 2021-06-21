// Fill out your copyright notice in the Description page of Project Settings.


#include "Spike.h"

ASpike::ASpike()
{
 	PrimaryActorTick.bCanEverTick = true;

	damage = 1;
	spikeType = ESpikeType::FIXED;
	beginDelay = 0.0f;
	activePeriod = 1.0f;
	deactivePeriod = 1.0f;

	activation = false;

	isBegin = true;
	currentTime = 0.0f;

	playAnimation = false;
	animationTime = 0.0f;

	spikeMesh = nullptr;
}

void ASpike::BeginPlay()
{
	Super::BeginPlay();
	
	spikeMesh = Cast<USceneComponent>(GetComponentsByTag(USceneComponent::StaticClass(), FName("SpikeMesh"))[0]);

	if (ESpikeType::FIXED == spikeType)
	{
		puzzleActive = true;
	}
	SwitchActive(puzzleActive);
}

void ASpike::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (activation)
	{
		if (OtherActor->ActorHasTag(FName("Character")))
		{
			OtherActor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
		}
	}
}

void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ð���� Ÿ���� ���� - �ð��� ���� ���º�ȭ
	if (ESpikeType::TIMELAPSE == spikeType && !IsHidden())
	{
		currentTime += DeltaTime;

		if (isBegin)
		{
			if (currentTime >= beginDelay)
			{
				currentTime = 0.0f;
				isBegin = false;
			}
		}
		else
		{
			if (activation)
			{
				if (currentTime >= activePeriod)
				{
					currentTime = 0.0f;
					SwitchActive(false);
				}
			}
			else
			{
				if (currentTime >= deactivePeriod)
				{
					currentTime = 0.0f;
					SwitchActive(true);
				}
			}
		}
	}

	// ���� ���º�ȭ �ִϸ��̼�
	if (playAnimation)
	{
		if (activation)
		{
			spikeMesh->SetRelativeLocation(FMath::Lerp(spikeMesh->GetRelativeLocation(), FVector(0.0f, 0.0f, 0.0f), DeltaTime * 10.0f));

			if (spikeMesh->GetRelativeLocation() == FVector(0.0f, 0.0f, 0.0f))
			{
				playAnimation = false;
			}
		}
		else
		{
			spikeMesh->SetRelativeLocation(FMath::Lerp(spikeMesh->GetRelativeLocation(), FVector(0.0f, 0.0f, -100.0f), DeltaTime * 10.0f));

			if (spikeMesh->GetRelativeLocation() == FVector(0.0f, 0.0f, 0.0f))
			{
				playAnimation = true;
			}
		}
	}
}

void ASpike::OnSwitch()
{
	if (ESpikeType::SWITCHABLE == spikeType)
	{
		// ���� ����ġ�� ������ ������ ���� ����
		SwitchActive(!puzzleActive);
	}
}

void ASpike::SwitchActive(bool Active)
{
	puzzleActive = Active;
	activation = Active;
	playAnimation = true;
}