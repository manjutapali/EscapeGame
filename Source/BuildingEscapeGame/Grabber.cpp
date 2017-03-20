// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscapeGame.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetUpInputComponent();
}

// Finds Physics handle 
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle Not found for %s"), *GetOwner()->GetName())
	}

}

void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component found"))
		
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input componet not found"));
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto Actor = HitResult.GetActor();

	if (Actor)
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			Actor->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Released()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))

		PhysicsHandle->ReleaseComponent();

}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);


	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	// Get player view point at this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Logging the PlayerViewPoints
	/*UE_LOG(LogTemp, Warning, TEXT("Location : %s"), *PlayerViewPointLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Rotation : %s"), *PlayerViewPointRotation.ToString());*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/// Collision parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line Trace out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// Logging the hit objects
	/*UE_LOG(LogTemp, Warning, TEXT("Object Name : %s"), *(Hit.GetActor()->GetName()));*/

	AActor *ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *(ActorHit->GetName()));
	}

	return Hit;
}

