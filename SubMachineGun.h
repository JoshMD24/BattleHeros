// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "SubMachineGun.generated.h"

UCLASS()
class BATTLEHEROS_API ASubMachineGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASubMachineGun();

	UFUNCTION(BlueprintCallable)
		void GetSubMachineGunQuality();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SubMachineGunQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SubMachineGunDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SubMachineGunFireRate;

	UFUNCTION(BlueprintCallable)
	void pickedUpSMG();

	void TestServer();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Pickup();
	bool Server_Pickup_Validate();
	void Server_Pickup_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_Pickup();
	bool Multi_Pickup_Validate();
	void Multi_Pickup_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
