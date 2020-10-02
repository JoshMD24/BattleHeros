// Fill out your copyright notice in the Description page of Project Settings.


#include "PhyscisBullet.h"

// Sets default values
APhysicsBullet::APhysicsBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));

	//Setting initial velocity
	ProjectileMovement->InitialSpeed = 200.0f;
	//Turn off gravity
	ProjectileMovement->ProjectileGravityScale = 0;
	//Set angular velocity
	angVel.Y = 45.0f;
}

// Called when the game starts or when spawned
void APhysicsBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APhysicsBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FQuat AngularVel(0, angVel.X, angVel.Y, angVel.Z);

	pos += vel * DeltaTime + 0.5f * DeltaTime * DeltaTime;
	vel += accel * DeltaTime;
	ori += (AngularVel * ori * (DeltaTime / 2));
	ori.Normalize();

	AngularVel = ori;

	//Set the object to update rotation using ori
	APhysicsBullet::SetActorRotation(ori);
}
