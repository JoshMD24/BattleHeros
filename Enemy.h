// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Waypoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/KismetMathLibrary.h"

#include "PlayerCharacter.h"

#include "Enemy.generated.h"

UCLASS()
class BATTLEHEROS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float health;

	int lootDropNumber;

	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, Category = Utility)
		UArrowComponent* BulletSpawnLocation;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Bullet;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> LootDrop;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> LootDropTwo;

	UFUNCTION(BlueprintCallable)
		void ShotByBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canShoot;

	UFUNCTION(BlueprintCallable)
		void Die();

	void StopShooting();

	UFUNCTION(BlueprintCallable)
		void MoveToWaypoints();

	UFUNCTION(BlueprintCallable)
		void ShootBullet();

	UPROPERTY(EditAnywhere, Category = AI)
		UAIPerceptionComponent* Perception;

	UPROPERTY(EditAnywhere, Category = AI)
		UAISenseConfig_Sight* Sight;

	UFUNCTION(BlueprintCallable)
	void LookAtPlayer();

	UFUNCTION(BlueprintCallable)
	void OnDeath();

	UFUNCTION(BlueprintCallable)
		void DropLoot();

	AActor* player;

	FTimerHandle DeathDelay;
	FTimerHandle ShootDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	int currentWaypoint;

	TArray<AActor*> Waypoints;
};
