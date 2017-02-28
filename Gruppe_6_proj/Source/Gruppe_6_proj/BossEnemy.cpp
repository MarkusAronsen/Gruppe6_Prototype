// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "BossEnemy.h"
#include "Bullet.h"
#include "MeleeAttack.h"
#include "BossBullet.h"


// Sets default values
ABossEnemy::ABossEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Error, TEXT("Boss has spawned"));

	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No collision box"));

	}

}

// Called every frame
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BulletWaveSpawnTimer = BulletWaveSpawnTimer + DeltaTime;

	switch (BossMode)
	{
	case 1:
		SetBossLocation(DeltaTime);
		SetBossRotation();
		if (BulletWaveSpawnTimer > 4.0f)
		{
			SpawnBossBulletWave();
			BulletWaveSpawnTimer = 0.0f;
		}

		break;

	case 2:
		SetBossLocation(DeltaTime);
		SetBossRotation();

		SpawnBossBulletStream(DeltaTime, AddYaw);

		break;
	}



}

void ABossEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Boss Overlap %s"), *OtherActor->GetName())

		if (OtherActor->IsA(ABullet::StaticClass()))
		{
			OtherActor->Destroy();
			BossHealth--;
			if (BossHealth < 1)
			{
				Destroy();
			}
		}
		else if (OtherActor->IsA(AMeleeAttack::StaticClass()))
		{

		}
}

void ABossEnemy::SetBossLocation(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;
	SetActorLocation(NewLocation);
}

void ABossEnemy::SetBossRotation()
{
	FVector BossLocation = GetActorLocation();
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - BossLocation;

	NewDirection.Z = 0.0f;
	NewDirection.Normalize();

	SetActorRotation(NewDirection.Rotation());
}

void ABossEnemy::SpawnBossBulletWave()
{
	World = GetWorld();

	FRotator CurrentRotation = GetActorRotation();

	FRotator AddYaw = FRotator(0.0f, 10.0f, 0.0f);

	FRotator NewRotation = CurrentRotation;

	FVector Location = GetActorLocation();

	for (int i = 0; i < 36; i++)
	{
		World->SpawnActor<ABossBullet>(BossBullet_BP, Location, NewRotation);
		NewRotation = NewRotation + AddYaw;
	}

	BossMode = 2;

}

void ABossEnemy::SpawnBossBulletStream(float DeltaTime, float &AddYaw)
{

	StopBulletStream = StopBulletStream + DeltaTime;
	StreamDelay = StreamDelay + DeltaTime;
	World = GetWorld();
	FVector Location = GetActorLocation();

	if (StreamDelay > 0.20f)
	{
		AddYaw = AddYaw + 15.0f;

		FRotator NewRotation = FRotator(0.0, AddYaw, 0.0);

		World->SpawnActor<ABossBullet>(BossBullet_BP, Location, NewRotation);
		StreamDelay = 0.0f;
	}

	if (StopBulletStream > 5.0f)
	{
		StopBulletStream = 0;
		BossMode = 1;
		AddYaw = 0;
	}


}