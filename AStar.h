// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AStarNodeGrid.h"

#include "CoreMinimal.h"
#include "RunnableThread.h"
#include "GameFramework/Actor.h"
#include "AStar.generated.h"

UENUM(BlueprintType)
enum class EHeuristic : uint8
{
	Heuristic_Manhatten 	UMETA(DisplayName = "Manhatten"),
	Heuristic_Euclidean 	UMETA(DisplayName = "Euclidean"),

};


UCLASS()
class BATTLEHEROS_API AAStar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAStar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EHeuristic Heuristic;

	UFUNCTION(BlueprintCallable, Category = "AStar")
		FVector FindPath(FVector Start, FVector End);

	//UFUNCTION(BlueprintCallable, Category = "Navigation-GL")
		//void DrawPath(TArray<PathfindingNode*> Path);

	FVector RetracePath(AAStarNode* StartNode, AAStarNode* EndNode);
	float GetDistance(AAStarNode* A, AAStarNode* B);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Pathfinding)
		AAStarNodeGrid* GridInstance;

	UPROPERTY(EditAnywhere, Category = Pathfinding)
		bool Debug;

};
