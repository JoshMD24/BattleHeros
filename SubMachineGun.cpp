// Fill out your copyright notice in the Description page of Project Settings.


#include "SubMachineGun.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASubMachineGun::ASubMachineGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASubMachineGun::BeginPlay()
{
	Super::BeginPlay();
	
	GetSubMachineGunQuality();
	bReplicates = true;
}

// Called every frame
void ASubMachineGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASubMachineGun::GetSubMachineGunQuality()
{
	SubMachineGunDamage = FMath::RandRange(1, 100);

	//Get SMG fire rate then round to nearest decimal by x10 then / 10
	SubMachineGunFireRate = FMath::RandRange(2.0f, 3.0f);
	SubMachineGunFireRate = SubMachineGunFireRate * 10;
	SubMachineGunFireRate = round(SubMachineGunFireRate);
	SubMachineGunFireRate = SubMachineGunFireRate / 10;

	SubMachineGunQuality = SubMachineGunDamage * SubMachineGunFireRate;
}

void ASubMachineGun::pickedUpSMG()
{
	if (this)
	{
		TestServer();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		Destroy();
	}
}

void ASubMachineGun::TestServer()
{
	Server_Pickup();
}

bool ASubMachineGun::Server_Pickup_Validate()
{
	return true;
}

void ASubMachineGun::Server_Pickup_Implementation()
{
	Multi_Pickup();
}

bool ASubMachineGun::Multi_Pickup_Validate()
{
	return true;
}

void ASubMachineGun::Multi_Pickup_Implementation()
{
	if (this)
	{
		
	}
}