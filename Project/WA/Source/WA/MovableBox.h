// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DefaultPuzzle.h"
#include "MovableBox.generated.h"

UCLASS()
class WA_API AMovableBox : public ADefaultPuzzle, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AMovableBox();

private:
	// Weather this object is in the air when game start.
	UPROPERTY(EditAnywhere, Category = "Gravity")
	bool isInAirOnStart;
	// Speed of gravity.
	UPROPERTY(EditAnywhere, Category = "Gravity")
	float gravitySpeed;
	bool inAir;
	float fallSpeed;

	FVector distance;

	UPROPERTY()
	class APlayerCharacter* pc;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void InitializePuzzle() override;

	virtual void Interact() override;

	// ĳ���Ϳ��� ������ ������ �����մϴ�.
	void ForceDisconnect();
};
