// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "SuicideEnemy.h"
#include "SuicideAttack.h"
#include "Bullet.h"


// Sets default values
ASuicideEnemy::ASuicideEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuicideEnemy::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASuicideEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No collision box"));

	}
	
}

// Called every frame
void ASuicideEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (EnemyMode)
	{
	case 1:
		SetEnemyLocation(DeltaTime);

		SetEnemyRotation();

		break;

	case 2:
		//Exec detonation

		Detonate(DeltaTime);

		break;
	}
}

void ASuicideEnemy::Detonate(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Execute Detonate"));
	TimeToExplode = TimeToExplode + DeltaTime;

	World = GetWorld();

	FVector SuicideEnemyLocation = GetActorLocation();

	if (TimeToExplode > 0.8f)
	{
		World->SpawnActor<ASuicideAttack>(SuicideAttack_BP, SuicideEnemyLocation, FRotator::ZeroRotator);
		//DeleteThisEnemy = true;
		//SetActorLocation(DestructionLocation);
		Destroy();
	}
}

void ASuicideEnemy::SetEnemyRotation()
{

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	//UE_LOG(LogTemp, Warning, TEXT("New Direction Size is: %f"), NewDirection.Size());

	if (NewDirection.Size() <= 100.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Exec Attack"));

		EnemyMode = 2;
	}

	NewDirection.Z = 0.0f;
	NewDirection.Normalize();
	SetActorRotation(NewDirection.Rotation());

}

void ASuicideEnemy::SetEnemyLocation(float DeltaTime)
{
	FVector NewLocation;

	NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);
}

void ASuicideEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
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
				//SetActorLocation(DestructionLocation);
				Destroy();
			}
		}
}

//void ASuicideEnemy::SetSuicideEnemyCounter(int &SuicideEnemyCounter)
//{
//	SuicideEnemyCounter = SuicideEnemyCounter + 1;
//}
