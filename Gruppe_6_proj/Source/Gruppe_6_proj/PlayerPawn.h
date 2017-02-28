// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MeleeAttack.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Move_Y_Axis(float AxisValue);

	void Move_X_Axis(float AxisValue);

	int PlayerHealth = 30;

	float MouseLocation_X;
	float MouseLocation_Y;

	UPROPERTY(EditAnywhere)
		AActor * Camera = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

	//UPROPERTY(EditAnywhere)
	//	USceneComponent * CursorObject;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABullet> Bullet_BP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AMeleeAttack> MeleeAttack_BP;

	FVector CurrentVelocity;

	void RotatePlayer();

	void Shoot();

	void MeleeAttack();



	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	class UDecalComponent* CursorToWorld;
	
	
};
