// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "EBullet.generated.h"

UCLASS()
class BATTLEHEROS_API AEBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEBullet();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	/** called when projectile hits something */
	UFUNCTION(BlueprintCallable)
		void OnOverlapBegin();

	void OnDestroy();

	FTimerHandle MyTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
