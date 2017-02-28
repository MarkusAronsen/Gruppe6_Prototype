// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "Bullet.h"
#include "Enemy.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));

	BulletVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Bullet"));

	BulletVisual->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Bullet Spawned"));

	SetBulletRotation();

	
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation;

	NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);

	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector Destruction = GetActorLocation() - PlayerPosition;

	if (Destruction.Size() >= 7000.0f)
	{
		//UE_LOG(LogTemp, Error, TEXT("Destruction"));

		Destroy();
	}


}

void ABullet::SetBulletRotation()
{
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		FVector CursorLocation = Hit.Location;

		//UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());

		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.0f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}
