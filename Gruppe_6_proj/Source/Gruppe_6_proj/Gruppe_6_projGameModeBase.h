// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Gruppe_6_projGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AGruppe_6_projGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AGruppe_6_projGameModeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


};