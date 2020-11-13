// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStarNode.generated.h"

UCLASS()
class BATTLEHEROS_API AAStarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	~AAStarNode();

	void AStarNodeFunction(int GridXPos, int GridYPos, int GridZPos);

	AAStarNode* ParentNode;
	int GridX, GridY, GridZ;
	int GCost = 0; // Cost so far
	int HCost = 0; // Heuristic 
	float FCost(); // Total cost

};
