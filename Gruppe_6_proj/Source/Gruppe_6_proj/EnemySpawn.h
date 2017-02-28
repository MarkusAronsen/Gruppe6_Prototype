// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"


UCLASS()
class GRUPPE_6_PROJ_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemy> Enemy_BP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ASuicideEnemy> SuicideEnemy_BP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AStrayEnemy> StrayEnemy_BP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABossEnemy> BossEnemy_BP;

	FVector EnemyLocation;

	UPROPERTY(VisibleAnywhere)
		UWorld * World;

	UPROPERTY(EditAnywhere)
		USceneComponent * VisibleSpawner;

	UPROPERTY()
		class AEnemy * StandardEnemyPtr;

	UPROPERTY()
		class ASuicideEnemy * SuicideEnemyPtr;

	void StandardSpawn(float DeltaTime);
	void SuicideSpawn(float DeltaTime);
	void StraySpawn(float DeltaTime);
	void RoundIntermission(float DeltaTime);
	void BossSpawn();

	float StraySpawnTimer;
	float SpawnTimer;
	float SuicideSpawnTimer;
	float RoundTimer = 0.0f;
	float StandardSpawnDelay = 3.0f;
	float SuicideSpawnDelay = 4.5f;
	float StraySpawnDelay = 5.0f;

	//int SuicideEnemiesInWorld = 0;
	int StandardEnemiesInWorld = 0;
	int Round = 1;

	
};
