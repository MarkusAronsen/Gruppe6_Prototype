// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BossBullet.generated.h"

UCLASS()
class GRUPPE_6_PROJ_API ABossBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossBullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	float Speed = 450.0f;
	float TimeToDestroy;

	UPROPERTY(EditAnywhere)
		USceneComponent * VisibleBossBullet;




};