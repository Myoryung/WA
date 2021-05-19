// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"


APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	playerCharacter = nullptr;
	speedLevel = 8.0f;

	defaultRelativeLocation = FVector::ZeroVector;
	defaultRelativeRotation = FRotator::ZeroRotator;

	relativeLocation = FVector::ZeroVector;
	relativeRotation = FRotator::ZeroRotator;

	prevRelativeLocation = FVector::ZeroVector;
	prevRelativeRotation = FRotator::ZeroRotator;

	overlapCount = 0;
}

void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (playerCharacter)
	{
		FVector target_pos = playerCharacter->GetActorLocation() + relativeLocation;
		target_pos.Z = relativeLocation.Z;	// ���� ����
		
		SetActorLocation(FMath::Lerp(
			GetActorLocation(), 
			target_pos, 
			DeltaTime * speedLevel));

		// ȸ�� ���°� �ٸ� ������ ȸ��
		if (GetActorRotation() != relativeRotation)
		{
			SetActorRotation(FMath::Lerp(
				GetActorRotation(),
				relativeRotation,
				DeltaTime * speedLevel));
		}
	}
}

void APlayerCamera::SetInitialize(AActor* Player, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	playerCharacter = Player;

	defaultRelativeLocation = RelativeLocation;
	defaultRelativeRotation = RelativeRotation;

	relativeLocation = RelativeLocation;
	relativeRotation = RelativeRotation;

	prevRelativeLocation = RelativeLocation;
	prevRelativeRotation = RelativeRotation;
}

void APlayerCamera::ChangeViewport(const FVector& Position, const FRotator& Rotation)
{
	prevRelativeLocation = relativeLocation;
	prevRelativeRotation = relativeRotation;
	
	relativeLocation = Position;
	relativeRotation = Rotation;

	overlapCount++;
}
void APlayerCamera::RevertViewport(const FVector& Position, const FRotator& Rotation)
{
	if (Position == relativeLocation && Rotation == relativeRotation)	// �ֿܰ��� �ִ� ViewChanger�� ȣ���� ���
	{
		if (overlapCount <= 1)	// ���� ��ȯ�� �� ���� �̷���� ���
		{
			relativeLocation = defaultRelativeLocation;
			relativeRotation = defaultRelativeRotation;
		}
		else					// ���� ��ȯ�� 2��ø �̻��� ���
		{
			relativeLocation = prevRelativeLocation;
			relativeRotation = prevRelativeRotation;
		}
	}

	overlapCount--;
}