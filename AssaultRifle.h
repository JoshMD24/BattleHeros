// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssaultRifle.generated.h"

UCLASS()
class BATTLEHEROS_API AAssaultRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAssaultRifle();

	UFUNCTION(BlueprintCallable)
		void GetAssaultRifleQuality();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AssaultRifleQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AssaultRifleDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssaultRifleFireRate;

	void pickedUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
