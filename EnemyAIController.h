// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine.h"
#include "GameFramework/Controller.h"
#include "EnemyAIController.generated.h"

UCLASS()
class BATTLEHEROS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
		void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
