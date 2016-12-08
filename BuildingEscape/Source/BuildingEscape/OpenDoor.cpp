// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	CloseDoor();

	FString objectName = Owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor component of %s"), *objectName);

}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll for PressurePlate overlap with ActorThatOpens
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		// UE_LOG(LogTemp, Warning, TEXT("pressure plate opening door %s"), *ActorThatOpens->GetName());
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}

	float now = GetWorld()->GetTimeSeconds();
	if ((now - DoorLastOpenTime) >= DoorOpenDelay)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	FRotator newRotation(0.0f, OpenAngle, 0.0f);
	Owner->SetActorRotation(newRotation);

	// UE_LOG(LogTemp, Warning, TEXT("Open door %s"), *Owner->GetName());
}

void UOpenDoor::CloseDoor()
{
	FRotator newRotation(0.0f, CloseAngle, 0.0f);
	Owner->SetActorRotation(newRotation);

	// UE_LOG(LogTemp, Warning, TEXT("Close door %s"), *Owner->GetName());
}

