// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "MeleeAttack.h"
#include "Enemy.h"
#include "SuicideEnemy.h"
#include "StrayEnemy.h"
#include "BossEnemy.h"


// Sets default values
AMeleeAttack::AMeleeAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Melee Spawned"));

	CollisionBox = this->FindComponentByClass<UBoxComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeAttack::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No collision box"));

	}

	SetMeleeRotation();

}

// Called every frame
void AMeleeAttack::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector MeleeLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	SetActorLocation(MeleeLocation);

	Timer = Timer + DeltaTime;

	if (Timer > 0.4f)
	{
		Destroy();
	}

	FRotator CurrentRotation = GetActorRotation();
	FRotator TemporaryValue = FRotator(0.0f, -7.0f, 0.0f);
	FRotator NewRotation = CurrentRotation + TemporaryValue;

	SetActorRotation(NewRotation);
}

void AMeleeAttack::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("MeleeAttack Overlap %s"), *OtherActor->GetName())

		if (OtherActor->IsA(AEnemy::StaticClass()))
		{
			OtherActor->Destroy();
		}
		else if (OtherActor->IsA(ASuicideEnemy::StaticClass()))
		{
			OtherActor->Destroy();
		}
		else if (OtherActor->IsA(AStrayEnemy::StaticClass()))
		{
			OtherActor->Destroy();
		}
		else if (OtherActor->IsA(ABossEnemy::StaticClass()))
		{
			BossInvincibility(AttackDuration);
		}
}

void AMeleeAttack::SetMeleeRotation()
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
		FRotator StartUpPos = GetActorRotation() + FRotator(0.0f, 120.0f, 0.0f);
		SetActorRotation(StartUpPos);

	}

}

void AMeleeAttack::BossInvincibility(float &AttackDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("BossInvincibility activated"));
	AttackDuration = AttackDuration + 0.1f;

	UE_LOG(LogTemp, Warning, TEXT("AttackDuration is: %f"), AttackDuration);
	if (AttackDuration > 0.2f)
	{
		//InflictDamage();
		AttackDuration = 0.0f;
	}

	
}