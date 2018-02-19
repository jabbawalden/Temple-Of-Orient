// Fill out your copyright notice in the Description page of Project Settings.

#include "RisingActorTest.h"


// Sets default values
ARisingActorTest::ARisingActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARisingActorTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARisingActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector StartLocation = GetActorLocation();
	FVector NewLocation = StartLocation;
	NewLocation.Z += 1.5f;
	SetActorLocation(NewLocation);

	//StartLocation 
	//EndLocation = NewLocation.z += 30.f
	//If NewLocation = EndLocation, NewLocation.Z will then -= 1.5f
	//
}

