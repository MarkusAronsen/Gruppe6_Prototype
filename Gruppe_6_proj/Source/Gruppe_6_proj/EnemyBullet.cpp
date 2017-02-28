// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "EnemyBullet.h"


// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	VisualEnemyBullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Bullet"));
	VisualEnemyBullet->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	SetBulletRotation();
	
}

// Called every frame
void AEnemyBullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime;

	SetActorLocation(NewLocation);

	Timer = Timer + DeltaTime;
	if (Timer > 10.0f)
	{
		Destroy();
	}
}

void AEnemyBullet::SetBulletRotation()
{

	FVector EnemyLocation = GetActorLocation();

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - EnemyLocation;

	NewDirection.Z = 0.0f;
	NewDirection.Normalize();

	SetActorRotation(NewDirection.Rotation());


}

