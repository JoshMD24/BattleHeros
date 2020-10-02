// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

// Sets default values
AAssaultRifle::AAssaultRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay()
{
	Super::BeginPlay();
	
	GetAssaultRifleQuality();
}

// Called every frame
void AAssaultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAssaultRifle::GetAssaultRifleQuality()
{
	AssaultRifleDamage = FMath::RandRange(1, 100);

	//Get Assault rifle fire rate then round to nearest decimal by x10 then / 10
	AssaultRifleFireRate = FMath::RandRange(2.0f, 3.0f);
	AssaultRifleFireRate = AssaultRifleFireRate * 10;
	AssaultRifleFireRate = round(AssaultRifleFireRate);
	AssaultRifleFireRate = AssaultRifleFireRate / 10;

	AssaultRifleQuality = AssaultRifleDamage * AssaultRifleFireRate;
}

void AAssaultRifle::pickedUp()
{
	Destroy();
}