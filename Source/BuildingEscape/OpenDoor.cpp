// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!Owner) { return; }
	BaseRotation = Owner->GetActorRotation();
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp,Error, TEXT("%s missing Pressure plate"), *GetOwner()->GetName())
	}
}

void UOpenDoor::OpenDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	DoorIsClosed = false;
}
void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(BaseRotation);
	DoorIsClosed = true;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorOnPlate() > TriggerMass) 
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay && !DoorIsClosed) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorOnPlate()
	{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors) 
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}
	
	return TotalMass; 
	}