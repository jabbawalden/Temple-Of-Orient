// Fill out your copyright notice in the Description page of Project Settings.

#include "RotateBridge.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT
// Sets default values for this component's properties
URotateBridge::URotateBridge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotateBridge::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressure plate"), *GetOwner()->GetName())
	}
	
}


float URotateBridge::GetTotalMass()
{
	float TotalMass = 0.f;
	//find all the overlapping actors
	TArray<AActor*> OverlappingActors;

	//protection if pressureplate not set or found
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s has been detected"), *Actor->GetName());
	}

	//iterate through them adding their masses
	return TotalMass;
}

// Called every frame
void URotateBridge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (GetTotalMass() >= TriggerMass) 
	{
		ObjectEventActivation.Broadcast();
	}
}

