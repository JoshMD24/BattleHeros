// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.2f);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	InitialLifeSpan = 3.0f;
}

void ABullet::LowerSphereRadius()
{
	if (hasLoweredRadius == false)
	{
		CollisionComp->SetSphereRadius(0.0f);
		hasLoweredRadius = true;
	}
}

void ABullet::IncreaseSphereRadius()
{
	if (hasLoweredRadius == true)
	{
		CollisionComp->SetSphereRadius(5.2f);
		hasLoweredRadius = false;
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.0f);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnOverlapBegin()
{
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ABullet::OnDestroy, 0.01f, true);
}

void ABullet::OnDestroy()
{
	Destroy();
}
