// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDroppedAssaultRifle.h"

// Sets default values
APlayerDroppedAssaultRifle::APlayerDroppedAssaultRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerDroppedAssaultRifle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerDroppedAssaultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerDroppedAssaultRifle::GetDroppedAssaultRifleQuality()
{

}

void APlayerDroppedAssaultRifle::pickedUp()
{
	Destroy();
}


