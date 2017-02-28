// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "EnemySpawn.h"
#include "Enemy.h"
#include "SuicideEnemy.h"
#include "StrayEnemy.h"
#include "BossEnemy.h"
#include "Gruppe_6_projGameModeBase.h"


// Sets default values
AEnemySpawn::AEnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCube"));

	VisibleSpawner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Spawner"));
	VisibleSpawner->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (Round)
	{
	case 1:
		//UE_LOG(LogTemp, Warning, TEXT("StandardSpawnDelay is: %f"), StandardSpawnDelay);
		if (StandardEnemiesInWorld <= 10)
		{
			StandardSpawn(DeltaTime);
			SuicideSpawn(DeltaTime);
			StraySpawn(DeltaTime);
		}
		else
		{
			RoundIntermission(DeltaTime);
		}
			//UE_LOG(LogTemp, Warning, TEXT("Round is; %i"), Round);
		break;

	case 2:
		//UE_LOG(LogTemp, Warning, TEXT("StandardSpawnDelay is: %f"), StandardSpawnDelay);
		StandardSpawnDelay = 2.0f;
		SuicideSpawnDelay = 3.0f;
		StraySpawnDelay = 5.0f;
		if (StandardEnemiesInWorld <= 15)
		{
			StandardSpawn(DeltaTime);
			SuicideSpawn(DeltaTime);
			StraySpawn(DeltaTime);
		}
		else
		{
			RoundIntermission(DeltaTime);
		}

		break;

	case 3:

		BossSpawn();

		Round = Round + 1;
		break;

	case 4:
		break;
	}
}

void AEnemySpawn::StandardSpawn(float DeltaTime)
{
	World = GetWorld();

	//WorldTime = GetWorld()->GetTimeSeconds();
	SpawnTimer = SpawnTimer + DeltaTime;
	SuicideSpawnTimer = SuicideSpawnTimer + DeltaTime;

	EnemyLocation = GetActorLocation();


	if (SpawnTimer >= StandardSpawnDelay)
	{
		StandardEnemyPtr = World->SpawnActor<AEnemy>(Enemy_BP, EnemyLocation, FRotator::ZeroRotator);
		StandardEnemyPtr->StandardEnemySpawnPtr = this;
		StandardEnemyPtr->SetStandardEnemyCounter(StandardEnemiesInWorld);
		SpawnTimer = 0.0f;
	}
}

void AEnemySpawn::SuicideSpawn(float DeltaTime)
{
	World = GetWorld();

	SuicideSpawnTimer = SuicideSpawnTimer + DeltaTime;

	EnemyLocation = GetActorLocation();

	if (SuicideSpawnTimer >= SuicideSpawnDelay)
	{
		//SuicideEnemyPtr = 
		World->SpawnActor<ASuicideEnemy>(SuicideEnemy_BP, EnemyLocation, FRotator::ZeroRotator);
		//SuicideEnemyPtr->SuicideEnemySpawnPtr = this;
		//SuicideEnemyPtr->SetSuicideEnemyCounter(SuicideEnemiesInWorld);
		SuicideSpawnTimer = 0.0f;
	}
}

void AEnemySpawn::StraySpawn(float DeltaTime)
{
	World = GetWorld();

	StraySpawnTimer = StraySpawnTimer + DeltaTime;

	EnemyLocation = GetActorLocation();

	if (StraySpawnTimer >= StraySpawnDelay)
	{
		World->SpawnActor<AStrayEnemy>(StrayEnemy_BP, EnemyLocation, FRotator::ZeroRotator);
		StraySpawnTimer = 0.0f;
	}


}

void AEnemySpawn::RoundIntermission(float DeltaTime)
{
	RoundTimer = RoundTimer + DeltaTime;

	if (RoundTimer > 10.0f)
	{
		StandardEnemiesInWorld = 0;
		Round = Round + 1;
		RoundTimer = 0.0f;
	}
	UE_LOG(LogTemp, Warning, TEXT("RoundTimer is: %f"), RoundTimer);
}

void AEnemySpawn::BossSpawn()
{
	World = GetWorld();
	EnemyLocation = GetActorLocation();

	World->SpawnActor<ABossEnemy>(BossEnemy_BP, EnemyLocation, FRotator::ZeroRotator);
}