// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SuicideEnemy.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API ASuicideEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuicideEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleAnywhere)
		UWorld * World;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ASuicideAttack> SuicideAttack_BP;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

	UPROPERTY()
		class AEnemySpawn * SuicideEnemySpawnPtr;

	void SetSuicideEnemyCounter(int &SuicideEnemyCounter);

	void SetSuicideEnemySubtraction(int &SuicideEnemySubtraction);

	int Health = 2;

	float Speed = 500.0f;

	void Detonate(float DeltaTime);

	void SetEnemyRotation();

	void SetEnemyLocation(float DeltaTime);
	
	int EnemyMode = 1;

	float TimeToExplode = 0.0f;

	bool DeleteThisEnemy = false;

	FVector DestructionLocation = FVector(0.0f, 0.0f, -100.0f);



};
