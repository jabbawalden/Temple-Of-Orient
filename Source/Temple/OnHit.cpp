// Fill out your copyright notice in the Description page of Project Settings.

#include "OnHit.h"


// Sets default values
AOnHit::AOnHit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOnHit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOnHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

