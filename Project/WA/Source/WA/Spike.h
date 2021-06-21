// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "Spike.generated.h"

UENUM(BlueprintType)
enum class ESpikeType : uint8
{
	FIXED UMETA(DisplayName = "Fixed"),
	SWITCHABLE UMETA(DisplayName = "Switchable"),
	TIMELAPSE UMETA(DisplayName = "Timelapse")
};

UCLASS()
class WA_API ASpike : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	ASpike();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void InitializePuzzle() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnSwitch() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spike")
	int damage;
	UPROPERTY(EditAnywhere, Category = "Spike")
	ESpikeType spikeType;
	UPROPERTY(EditAnywhere, Category = "Spike|Timelapse")
	float beginDelay;
	UPROPERTY(EditAnywhere, Category = "Spike|Timelapse")
	float activePeriod;
	UPROPERTY(EditAnywhere, Category = "Spike|Timelapse")
	float deactivePeriod;

	// ���� Ȱ��ȭ ����. true�� �� ���ð� �ö�� ����
	bool activation;

	// beginDelay ������ �̿��� �ʱ� �۵� �����̸� �� ������ ����
	bool isBegin;
	// ���� �۵� �ð�
	float currentTime;

	// ���� �۵� �ִϸ��̼� ���� ����
	bool playAnimation;
	// ���� �۵� �ִϸ��̼� ���� �ð�
	float animationTime;

	UPROPERTY()
	USceneComponent* spikeMesh;


	// ������ Ȱ��ȭ ���θ� �����մϴ�.
	void SwitchActive(bool Active);
};
