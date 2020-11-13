// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStarNode.h"
#include "AStarNodeGrid.generated.h"

UCLASS()
class BATTLEHEROS_API AAStarNodeGrid : public AActor
{
	GENERATED_BODY()

private:
	void BuildGrid();
	void DebugGrid();


public:
	// Sets default values for this actor's properties
	AAStarNodeGrid();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
		FVector GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
		float NodeSize;

	UPROPERTY(EditAnywhere, Category = Grid)
		TArray<TEnumAsByte<EObjectTypeQuery>> Trace;

	UPROPERTY(EditAnywhere, Category = Grid)
		bool DebugDraw;

	AAStarNode* NodeFromLocation(FVector const& Loc);
	FVector LocationFromNode(AAStarNode* const& Node);
	TArray<AAStarNode*> GetNeighbourNodes(AAStarNode* const& Node);

	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	TArray<TArray<TArray<AAStarNode*>>> NodeGrid;
};
