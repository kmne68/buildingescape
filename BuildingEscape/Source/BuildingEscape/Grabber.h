// Copyright Keith Emery 2018

#pragma once

#include "DrawDebugHelpers.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far the player can reach (in cm)
	float reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();

	// Called when Grab() is released
	void Release();
	
	// Finda attached physics handle
	void FindPhysicsHandleComponent();

	// Set up input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach();			// removed const from this to get it to run

	// Returns current start of reach line
	FVector GetReachLineStart();

		// Returns current end of reach line
	FVector GetReachLineEnd();

};
