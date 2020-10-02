// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "PhyscisBullet.generated.h"

UCLASS()
class BATTLEHEROS_API APhysicsBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	FVector pos;
	FVector rotation;
	FVector accel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector angVel;
	FVector vel;
	FQuat angularVelocity;
	FQuat ori;
};
