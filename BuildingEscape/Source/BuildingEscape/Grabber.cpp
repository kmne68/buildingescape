// Copyright Keith Emery 2018

#include "Grabber.h"
#include "BuildingEscape.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


	/// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// Physics handle is found

		UE_LOG(LogTemp, Warning, TEXT("Grabber active"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
}



	/// Look for attached input component (only appears at runtime)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		// Input component is found
		// UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}

}


void UGrabber::Grab() {

	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	/// LINE TRACE to see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	/// If we hit something, then attach a physics handle
	// TODO attach physics handle

}



void UGrabber::Release() {

	UE_LOG(LogTemp, Warning, TEXT("Grab released"));

	// TODO Release physics handle

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached...
		// ...move the object we are holding



}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{

	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Log out to test
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
	//	*PlayerViewPointLocation.ToString(),
	//	*PlayerViewPointRotation.ToString()
	//);

	//FVector LineTraceEnd = PlayerViewPointLocation + FVector(0.f, 0.f, 100.f); // viewpoint + 100cm up

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * reach);


	///	DEBUG CODE: Draw a red trace in the direction the player is looking
	//DrawDebugLine(
	//	GetWorld(),
	//	PlayerViewPointLocation,
	//	LineTraceEnd,
	//	FColor(255, 0, 0),
	//	false,
	//	0.f,
	//	0.f,
	//	10.f
	//);

	/// Set up query parameters
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (aka ray-cast) out to reach distance
	FHitResult hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters
	);

	/// See what we hit
	AActor* actorHit = hit.GetActor();
	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorHit->GetName()));
	}

	/// See what player sees

	return FHitResult();
}

