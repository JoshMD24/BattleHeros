// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarNode.h"

void AAStarNode::BeginPlay()
{
}

void AAStarNode::Tick(float DeltaTime)
{
}

AAStarNode::AAStarNode()
{

}

AAStarNode::~AAStarNode()
{
}

void AAStarNode::AStarNodeFunction(int GridXPos, int GridYPos, int GridZPos)
{
	GridX = GridXPos;
	GridY = GridYPos;
	GridZ = GridZPos;
}

float AAStarNode::FCost()
{
	return HCost + GCost;
}