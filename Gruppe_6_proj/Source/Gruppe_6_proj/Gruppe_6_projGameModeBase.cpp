// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "Gruppe_6_projGameModeBase.h"
#include "Enemy.h"

//AGruppe_6_projGameModeBase::AGruppe_6_projGameModeBase()

AGruppe_6_projGameModeBase::AGruppe_6_projGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;

}

void AGruppe_6_projGameModeBase::BeginPlay()
{

	Super::BeginPlay();

}

// Called every frame
void AGruppe_6_projGameModeBase::Tick(float DeltaTime)
{

	//UE_LOG(LogTemp, Error, TEXT("Game Mode Tick"));
	Super::Tick(DeltaTime);

}