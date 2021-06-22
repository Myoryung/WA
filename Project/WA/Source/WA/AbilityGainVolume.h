// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityGainVolume.generated.h"

UCLASS()
class WA_API AAbilityGainVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AAbilityGainVolume();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// �ش� ���� �۵� ����. 1ȸ�� �۵��̹Ƿ� bool type check�� ����, ������Ʈ ���ŷ� ���� ���ؾ� ��
	bool isUsed;
	// ī�޶� ������ �۵��ϰ� �ִ����� ����
	bool isDirectingWork;

	float timeline;
	float directingAngle;
	float directingVel;

	FVector characterPosition;

	UPROPERTY(EditAnywhere, Category = "Directing")
	float rotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* gatchaEffect;

	UPROPERTY()
	class APlayerCharacter* playerCharacter;
	UPROPERTY()
	class APlayerCamera* playerCam;


	void CameraDirecting(float DeltaTime);
};
