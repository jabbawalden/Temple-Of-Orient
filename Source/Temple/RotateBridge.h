// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "RotateBridge.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLE_API URotateBridge : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotateBridge();

	UPROPERTY(BlueprintAssignable)
		FRotateEvent BridgeRotateEvent;
	UPROPERTY(BlueprintAssignable)
		FRotateEvent BridgeStillEvent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMass;

	float GetTotalMass();

	AActor* Owner = nullptr;

		
	
};
