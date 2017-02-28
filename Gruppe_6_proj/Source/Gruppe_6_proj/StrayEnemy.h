// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StrayEnemy.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API AStrayEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStrayEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere)
		UWorld * World;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AStrayBullet> StrayBullet_BP;

	void SetEnemyLocation(float DeltaTime);
	void SetEnemyRotation();
	void SpawnStrayBullet();

	float Speed = 150.0f;
	float RotationTimer;
	float AttackTimer;

	int EnemyMode = 1;
	int Health = 5;

	
};
