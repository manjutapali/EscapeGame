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
	
}


// Called to open the door

void UOpenDoor::RotateDoorZ()
{
	// Accessing the owner
	FString OwnerName = GetOwner()->GetName();

	//Setting rotation for the door
	//UE_LOG(LogTemp, Warning, TEXT("Rotating the %s to 75 degrees"), *OwnerName);

	AActor* Owner = GetOwner();

	FRotator newRotation = FRotator(0.f, 75.0f, 0.f);

	Owner->SetActorRotation(newRotation);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...

	// Poll everyframe
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		RotateDoorZ();
	}

}

