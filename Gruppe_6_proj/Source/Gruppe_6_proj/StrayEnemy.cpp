// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "StrayEnemy.h"
#include "StrayBullet.h"
#include "Bullet.h"


// Sets default values
AStrayEnemy::AStrayEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrayEnemy::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStrayEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No collision box"));

	}

	SetEnemyRotation();
	
}

// Called every frame
void AStrayEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	RotationTimer = RotationTimer + DeltaTime;
	AttackTimer = AttackTimer + DeltaTime;

		SetEnemyLocation(DeltaTime);

		if (RotationTimer >= 5.0f)
		{
			SetEnemyRotation();
			RotationTimer = 0.0f;
		}
		if (AttackTimer >= 5.0f)
		{
			SpawnStrayBullet();
			AttackTimer = 0.0f;
		}
}

void AStrayEnemy::SetEnemyRotation()
{

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	NewDirection.Z = 0.0f;
	NewDirection.Normalize();
	SetActorRotation(NewDirection.Rotation());

}

void AStrayEnemy::SetEnemyLocation(float DeltaTime)
{
	FVector NewLocation;

	NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);
}

void AStrayEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
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

void AStrayEnemy::SpawnStrayBullet()
{
	FVector EnemyLocation = GetActorLocation();
	FRotator BulletRotation = GetActorRotation();
	FRotator TempRotation = GetActorRotation();
	FRotator AddYaw = FRotator(0.0f, 30.0f, 0.0f);

	World = GetWorld();

	for (int i = 0; i < 12; i++)
	{
		World->SpawnActor<AStrayBullet>(StrayBullet_BP, EnemyLocation, BulletRotation);
		BulletRotation = BulletRotation + AddYaw;
	}

	BulletRotation = TempRotation;
}
