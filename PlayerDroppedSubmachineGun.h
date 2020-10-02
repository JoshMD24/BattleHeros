// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerDroppedSubmachineGun.generated.h"

UCLASS()
class BATTLEHEROS_API APlayerDroppedSubmachineGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerDroppedSubmachineGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DroppedSubmachineGunQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DroppedSubmachineGunDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DroppedSubmachineGunFireRate;


	void pickedUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
