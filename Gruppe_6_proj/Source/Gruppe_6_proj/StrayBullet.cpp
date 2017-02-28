// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "StrayBullet.h"


// Sets default values
AStrayBullet::AStrayBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));

	//VisibleStrayBullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	//VisibleStrayBullet->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AStrayBullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStrayBullet::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No collision box"));

	}
	
}

// Called every frame
void AStrayBullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;
	SetActorLocation(NewLocation);

	TimerToDestroy = TimerToDestroy + DeltaTime;

	if (TimerToDestroy > 1.5f)
	{
		Destroy();
	}

}

void AStrayBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Overlap %s"), *OtherActor->GetName())

	//if (OtherActor->IsA(ABullet::StaticClass()))
	//{
		//Health--;
		//OtherActor->Destroy();
		//if (Health < 1)
		//{
			//DeleteThisEnemy = true;
			//SetActorLocation(DestructionLocation)
			//Destroy();
		//}
	//}
}

