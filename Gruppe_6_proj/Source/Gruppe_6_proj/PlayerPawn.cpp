// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "PlayerPawn.h"
#include "Bullet.h"
#include "MeleeAttack.h"
#include "EnemyBullet.h"
#include "SuicideAttack.h"
#include "StrayBullet.h"
#include "BossBullet.h"



// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetViewTarget(Camera);

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;

	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerPawn::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No collision box"));

	}

	//MyController->bEnableMouseOverEvents = true;

	//MyController->GetMousePosition(MouseLocation_X, MouseLocation_Y);



	//GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	RotatePlayer();

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveY", this, &APlayerPawn::Move_Y_Axis);
	InputComponent->BindAxis("MoveX", this, &APlayerPawn::Move_X_Axis);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerPawn::Shoot);
	InputComponent->BindAction("MeleeAttack", IE_Pressed, this, &APlayerPawn::MeleeAttack);
}

void APlayerPawn::Move_Y_Axis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f)*300.0f;

}

void APlayerPawn::Move_X_Axis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f)*300.0f;
}

void APlayerPawn::Shoot()
{
	//UE_LOG(LogTemp, Error, TEXT("Shoot"));

	UWorld * World;

	World = GetWorld();

	FVector Location = GetActorLocation();

	World->SpawnActor<ABullet>(Bullet_BP, Location, FRotator::ZeroRotator);
}
//void APlayerPawn::RotatePlayer()
//{
	    //if (Controller != NULL)
	    //{
	    //    FVector mouseLocation, mouseDirection;
	    //    APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	    //    playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
	    //   
	    //    //UE_LOG(LogTemp, Warning, TEXT("Mouse Location %s Direction %s"), *mouseLocation.ToString(), *mouseDirection.ToString());
	    //    
	    //    FRotator currentCharacterRotation = GetActorRotation();
	    //    FRotator targetRotation = mouseDirection.Rotation();
	    //    
	    //    FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw * YawSpeed, currentCharacterRotation.Roll);
	    //    SetActorRotation(newRotation);
	    //}

void APlayerPawn::MeleeAttack()
{
	//UE_LOG(LogTemp, Warning, TEXT("Melee Attack!"));



	UWorld * World;

	World = GetWorld();

	FVector Location = GetActorLocation();

	World->SpawnActor<AMeleeAttack>(MeleeAttack_BP, Location, FRotator::ZeroRotator);

}



//}

void APlayerPawn::RotatePlayer()
{
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		FVector CursorLocation = Hit.Location;

//		UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());

		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.0f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
}

void APlayerPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Player Overlap %s"), *OtherActor->GetName())

	if (OtherActor->IsA(AEnemyBullet::StaticClass()))
	{
		PlayerHealth--;
		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Player Health is: %i"), PlayerHealth);
		if (PlayerHealth < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("You died. Rip in pieces"));
		}
	}
	else if(OtherActor->IsA(ASuicideAttack::StaticClass()))
	{
		PlayerHealth--;
		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Player Health is: %i"), PlayerHealth);
		if (PlayerHealth < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("You died. Rip in pieces"));
		}
	}
	else if(OtherActor->IsA(AStrayBullet::StaticClass()))
	{
		PlayerHealth--;
		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Player Health is: %i"), PlayerHealth);
		if (PlayerHealth < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("You died. Rip in pieces"));
		}
	}
	else if(OtherActor->IsA(ABossBullet::StaticClass()))
	{
		PlayerHealth--;
		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Player Health is: %i"), PlayerHealth);
		if (PlayerHealth < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("You died. Rip in pieces"));
		}
	}

}





//void RotateToMouseCursor() {
//	// Get current mouse rotation
//	FVector mouseLocation, mouseDirection;
//	this->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
//
//	// Get local reference to the controller's character and its rotation
//	ACharacter *currentChar = this->GetCharacter();
//	FRotator charRotation = currentChar->GetActorRotation();
//
//	// Get the rotation of the mouse direction
//	FRotator targetRotation = mouseDirection.Rotation();
//
//	// Since I only want to turn the character relative to the ground, 
//	// the Yaw is the only change needed.
//	FRotator newRot = FRotator(charRotation.Pitch, targetRotation.Yaw, charRotation.Roll);
//
//	currentChar->SetActorRotation(newRot);
//}
