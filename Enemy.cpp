// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = 100;

	BulletSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletSpawnLocation"));
	BulletSpawnLocation->SetupAttachment(RootComponent);

	Perception = CreateDefaultSubobject< UAIPerceptionComponent>(TEXT("Perception"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	Sight->SightRadius = 500;
	Sight->LoseSightRadius = 600;
	Sight->PeripheralVisionAngleDegrees = 180.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	Perception->ConfigureSense(*Sight);
}
// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), Waypoints);
	/*MoveToWaypoints();*/

	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player)
	{
		velocity = player->GetActorLocation() - AEnemy::GetActorLocation();
		velocity.Normalize();
		velocity *= GetCharacterMovement()->MaxWalkSpeed;

		orientation = player->GetActorLocation();

		AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());
		EnemyAIController->MoveToLocation(velocity);
		AEnemy::SetActorRotation(orientation.Rotation());
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::ShotByBullet()
{
	if (player)
	{
		Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		health = health - Player->equippedGunDamage;

		if (health <= 0.0f)
		{
			OnDeath();
		}
	}
}

void AEnemy::OnDeath()
{
	DropLoot();

	Die();
	GetWorldTimerManager().SetTimer(DeathDelay, this, &AEnemy::Die, 0.01f, true);
}

void AEnemy::DropLoot()
{
	Player->money += 5;

	lootDropNumber = FMath::RandRange(1, 2);

	UWorld* World = GetWorld();

	FVector spawnLocation = BulletSpawnLocation->GetComponentLocation();
	FRotator spawnRotation = GetControlRotation();

	if (lootDropNumber == 1)
	{
		World->SpawnActor(LootDrop, &spawnLocation, &spawnRotation);
	}
	if (lootDropNumber == 2)
	{
		World->SpawnActor(LootDropTwo, &spawnLocation, &spawnRotation);
	}
}

void AEnemy::Die()
{
	Destroy();
}

void AEnemy::StopShooting()
{
	GetWorldTimerManager().ClearTimer(ShootDelay);
}

void AEnemy::MoveToWaypoints()
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());

	if (EnemyAIController)
	{
		if (currentWaypoint < Waypoints.Num())
		{
			for (AActor* Waypoint : Waypoints)
			{
				AWaypoint* WaypointItr = Cast<AWaypoint>(Waypoint);

				if (WaypointItr)
				{
					if (WaypointItr->GetWaypointOrder() == currentWaypoint)
					{
						EnemyAIController->MoveToActor(WaypointItr, 0.1f, false);
						currentWaypoint++;
						break;
					}
				}
			}
		}
	}
}

void AEnemy::ShootBullet()
{
	player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (player)
	{
			GetWorldTimerManager().SetTimer(ShootDelay, this, &AEnemy::ShootBullet, 0.2f, true);

			UWorld* World = GetWorld();

			/*FVector spawnLocation = GetActorLocation() + FVector(50.0f, 0.0f, 0.0f);*/
			FVector spawnLocation = BulletSpawnLocation->GetComponentLocation();
			FRotator spawnRotation = BulletSpawnLocation->GetComponentRotation();
			//World->SpawnActor(Bullet, &spawnLocation, &spawnRotation);
		
			//AI class
			shootOrientation = player->GetActorLocation();
			AEnemy::SetActorRotation(shootOrientation.Rotation());

			missChance = FMath::RandRange(1, 10);

			if (missChance <= 2)
			{
				spawnLocation = BulletSpawnLocation->GetComponentLocation() + FVector(300.0f, 0.0f, 0.0f);
			}
			else if (missChance > 2 && missChance <= 4)
			{
				spawnLocation = BulletSpawnLocation->GetComponentLocation() + FVector(-300.0f, 0.0f, 0.0f);
			}

			World->SpawnActor(Bullet, &spawnLocation, &spawnRotation);

	}
}

void AEnemy::LookAtPlayer()
{
		player = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (player)
		{
			player->GetActorLocation();

			FRotator EnemyRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), player->GetActorLocation());

			SetActorRotation(EnemyRot);
		}
}

//// A* Pathfinding
//std::unordered_map<Hex, Hex> AMapManager::FindPath(Hex start, Hex goal)
//{
//	// The optimal path.
//	std::unordered_map<Hex, Hex> cameFrom = { {start, start} };
//	// The cost to reach each hex
//	std::unordered_map<Hex, int> costSoFar = { {start, 0} };
//
//	// A sorted queue of hexes (cheapest in front) of all available tiles you can move to.
//	PriorityQueue<Hex> availableMoves;
//	availableMoves.put(start, 0); // Add the starting tile with 0 cost.
//
//	// While we still have nodes to search
//	while (!availableMoves.empty())
//	{
//		// Get the next cheapest tile.
//		auto current = availableMoves.get();
//
//		// If it is the goal, we are done.
//		if (current == goal)
//			break;
//
//		// Cycle through the current hex's neighbors
//		for (int i = 0; i < 6; ++i)
//		{
//			// Get the neighbor
//			auto neighbor = current.neighbor(current, i);
//
//			// Calculate its cost
//			int neighborCost = costSoFar[current] + GetHexCost(FVector(neighbor.q, neighbor.r, neighbor.s));
//
//			// If the neighbor is not already available, OR
//			// If the neighbor is available but we found a cheaper path to it
//			if (!costSoFar.count(neighbor) || neighborCost < costSoFar[neighbor])
//			{
//				// Set the cost for the neighbor to the calculated cost
//				costSoFar[neighbor] = neighborCost;
//
//				// Its priority is its cost + its distance to the goal
//				int priority = neighborCost + neighbor.distance(neighbor, goal);
//
//				// Add the neighbor to the available moves
//				availableMoves.put(neighbor, priority);
//
//				// Add the current hex to the optimal path
//				cameFrom[neighbor] = current;
//			}
//		}
//	}
//
//	return cameFrom;
//}
