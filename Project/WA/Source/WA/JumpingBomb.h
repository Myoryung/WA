// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpingBomb.generated.h"

UCLASS()
class WA_API AJumpingBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	AJumpingBomb();

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<AActor> bombEffect;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float jumpHeight;

	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* bombSound;

	UPROPERTY()
	class APlayerCharacter* playerCharacter;
	FVector startPos;
	FVector targetPos;
	float curTime;
	float travelTime;

	int32 jumpCount;

public:
	/// <summary>
	/// ��ź�� �߻��մϴ�.
	/// </summary>
	/// <param name="PlayerCharacter">ĳ���Ϳ� ���� ������. �ش� ������Ʈ�� ĳ���͸� �����ϴ� ���� �ʿ��մϴ�.</param>
	/// <param name="TravelTime">���� �ð�. �� �߻縶�� �����ϰ� ����˴ϴ�.</param>
	/// <param name="JumpCount">���� Ƚ��. �� ó�� �߻� ���� 1ȸ�� �������ϴ�.</param>
	void FireBomb(APlayerCharacter* PlayerCharacter, float TravelTime, int32 JumpCount);
};
