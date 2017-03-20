// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscapeGame.h"
#include "OpenDoor.h"

#define OUT

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
	if (GetMassOnPressurePlate() >= 10)
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

float UOpenDoor::GetMassOnPressurePlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Actor Name = "),*Actor->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("Total mass %f"), TotalMass);

	return TotalMass;
}