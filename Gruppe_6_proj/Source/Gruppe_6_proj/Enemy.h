// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		USceneComponent * EnemyVisual;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemyBullet> EnemyBullet_BP;

	UPROPERTY(VisibleAnywhere)
		UWorld * World;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

	UPROPERTY()
		class AEnemySpawn * StandardEnemySpawnPtr;

	void SetStandardEnemyCounter(int &StandardEnemyCounter);
	void SetEnemyRotation();
	void SetEnemyLocation(float DeltaTime);
	void EnemyShoot(float DeltaTime);

	int EnemyMode = 1;
	int Health = 3;

	float ShootTimer;
	float Speed = 200.0f;
	
	bool DeleteThisEnemy = false;

	FVector DestructionLocation = FVector(0.0f, 0.0f, -100.0f);
};
