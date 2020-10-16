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