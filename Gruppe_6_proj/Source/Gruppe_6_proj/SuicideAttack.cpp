// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "SuicideAttack.h"


// Sets default values
ASuicideAttack::ASuicideAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCube"));

	SuicideAttackVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Explosion"));

	SuicideAttackVisual->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASuicideAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuicideAttack::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator CurrentRotation = GetActorRotation();
	FRotator TemporaryValue = FRotator(0.0f, -10.0f, 0.0f);
	FRotator NewRotation = CurrentRotation + TemporaryValue;

	SetActorRotation(NewRotation);

	Timer = Timer + DeltaTime;
	if (Timer > 0.5)
	{
		Destroy();
	}
}

