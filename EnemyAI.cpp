// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	state = 1;
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (state == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Guarding"));

		if (canSeePlayer == true)
		{
			state = 2;
		}
	}
	if (state == 2)
	{
		if (canSeePlayer == true)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Chasing"));
		}	
		else
		{
			state = 3;
		}
	}
	if (state == 3)
	{
		Look();
	}
}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyAI::Guard()
{
	state = 1;
}

void AEnemyAI::Look()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Looking For Player"));

	if (canSeePlayer == false)
	{
		GetWorldTimerManager().SetTimer(CheckSightDelay, this, &AEnemyAI::Guard, 5.0f, true);
	}
	else
	{
		Chase();
		state = 2;
	}
}