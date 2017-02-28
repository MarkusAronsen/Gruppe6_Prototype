// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BossEnemy.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API ABossEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABossBullet> BossBullet_BP;

	UPROPERTY()
		UWorld * World;

	int BossHealth = 150;

	float Speed = 100.0f;

	float BulletWaveSpawnTimer;

	float AddYaw;

	float StreamDelay;

	int BossMode = 1;

	void SetBossLocation(float DeltaTime);
	void SetBossRotation();
	void SpawnBossBulletWave();
	void SpawnBossBulletStream(float DeltaTime, float &AddYaw);

	float StopBulletStream;
};
