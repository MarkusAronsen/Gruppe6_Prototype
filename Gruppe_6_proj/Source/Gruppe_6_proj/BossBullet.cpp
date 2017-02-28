// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_proj.h"
#include "BossBullet.h"


// Sets default values
ABossBullet::ABossBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));

	VisibleBossBullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	VisibleBossBullet->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABossBullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToDestroy = TimeToDestroy + DeltaTime;
	if (TimeToDestroy > 20.0f)
	{
		Destroy();
	}

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);




}