// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/World.h"

#include "PlayerDroppedAssaultRifle.generated.h"

UCLASS()
class BATTLEHEROS_API APlayerDroppedAssaultRifle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerDroppedAssaultRifle();

	UFUNCTION(BlueprintCallable)
		void GetDroppedAssaultRifleQuality();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DroppedAssaultRifleQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DroppedAssaultRifleDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DroppedAssaultRifleFireRate;


	void pickedUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
