// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MeleeAttack.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API AMeleeAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeAttack();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

	UPROPERTY(EditAnywhere)
		USceneComponent * MeleeAttackVisual;
	
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	float Timer = 0.0f;
	float AttackDuration = 0.0f;

	void SetMeleeRotation();
	void BossInvincibility(float &AttackDuration);

	UPROPERTY()
		class ABossEnemy * BossPtr;
};
