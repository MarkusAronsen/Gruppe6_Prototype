// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include "EnemySpawn.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No collision box"));

	}
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (EnemyMode)
	{
	case 1:
		SetEnemyLocation(DeltaTime);

		SetEnemyRotation();

		break;

	case 2:
		//Exec attack

		SetEnemyRotation();
		EnemyShoot(DeltaTime);

		break;

	case 3:
		//Exec flee

		break;
	}
}

void AEnemy::SetEnemyRotation()
{

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	if (NewDirection.Size() <= 700.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Exec Attack"));

		EnemyMode = 2;
	}

	NewDirection.Z = 0.0f;
	NewDirection.Normalize();
	SetActorRotation(NewDirection.Rotation());

}

void AEnemy::SetEnemyLocation(float DeltaTime)
{
	FVector NewLocation;

	NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);
}

void AEnemy::EnemyShoot(float DeltaTime)
{
	World = GetWorld();

	ShootTimer = ShootTimer + DeltaTime;

	FVector Location = GetActorLocation();

	//UE_LOG(LogTemp, Warning, TEXT("ShootTimer: %f"), ShootTimer);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	if (NewDirection.Size() > 700.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Exec Attack"));

		//World->SpawnActor<AEnemyBullet>(EnemyBullet_BP, Location, FRotator::ZeroRotator);

		EnemyMode = 1;
	}

	if (ShootTimer >= 2.5f)
	{

	World->SpawnActor<AEnemyBullet>(EnemyBullet_BP, Location, FRotator::ZeroRotator);
	ShootTimer = 0.0f;

	//UE_LOG(LogTemp, Error, TEXT("Enemy shooting"));

	}
}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Overlap %s"), *OtherActor->GetName())

		if (OtherActor->IsA(ABullet::StaticClass()))
		{
			Health--;
			OtherActor->Destroy();
			if (Health < 1)
			{
				//DeleteThisEnemy = true;
				//SetActorLocation(DestructionLocation)
				Destroy();
			}
		}
}

void AEnemy::SetStandardEnemyCounter(int &StandardEnemyCounter)
{
	StandardEnemyCounter = StandardEnemyCounter + 1;
}