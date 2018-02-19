// Copyright John 2018
#pragma once

#include "OGrabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h" 
#include "Engine/World.h"
#include "Gameframework/Actor.h"

#define OUT
// Sets default values for this component's properties
UOGrabber::UOGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Look for attached Physics Handle

}

// Called when the game starts
void UOGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetUpInputComponent();
}

//Look for attached Physics Handle
void UOGrabber::FindPhysicsHandleComponent()
{
	//look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}


}

//Look for attached Input Component (only appears at runtime)
void UOGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!InputComponent) { return; }

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UOGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UOGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input componenet"), *GetOwner()->GetName())
	}
}



void UOGrabber::Grab()
{
	//line trace and see if we reach any actos with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); //gets the mesh in our case
	auto ActorHit = HitResult.GetActor();

	//if we hit something, attach physics handle
	if (!PhysicsHandle) { return; }

	if (ActorHit != nullptr)
	{
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}

}

void UOGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

FHitResult UOGrabber::GetFirstPhysicsBodyInReach() const
{

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		///using :: to access members in an enum, which is what ECollisionChannel is
		TraceParameters
	);

	return HitResult;
}

FVector UOGrabber::GetReachLineStart() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPortRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,
		OUT PlayerViewPortRotation);

	return PlayerViewPointLocation;

}

FVector UOGrabber::GetReachLineEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPortRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,
		OUT PlayerViewPortRotation);

	return PlayerViewPointLocation + PlayerViewPortRotation.Vector() * Reach;

}

// Called every frame
void UOGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetFirstPhysicsBodyInReach();

	//to protect pointer - if no physicshandle alotted in Unreal, return before executing below code
	//avoids crashes
	if (!PhysicsHandle) { return; }

	if (PhysicsHandle->GrabbedComponent)
	{
		//move the object we are holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}

}

