// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscapeGame.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}


// Called to open the door

void UOpenDoor::OpenDoor()
{
	
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

// called to close the door

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...

	// Poll everyframe
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();

		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// check if it's time to close

	float CurrentTimeSeconds = GetWorld()->GetTimeSeconds();


	if ((LastDoorOpenTime + DoorCloseDelay) <= CurrentTimeSeconds)
	{
		CloseDoor();
	}

}

