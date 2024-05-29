// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s | Configured Move Distance: %f"), *Name, MoveDistance);
	// UE_LOG(LogTemp, Warning, TEXT("Your message"));
	// UE_LOG(LogTemp, Error, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!disabled) {
		MovePlatform(DeltaTime);
		RotatePlatform(DeltaTime);
	}

}

void AMovingPlatform::MovePlatform(float DeltaTime) {

	if (ShouldPlatformReturn()) {
		// float OverShoot = DistanceMoved - MoveDistance;
		// UE_LOG(LogTemp, Display, TEXT("%s Platform overshot by %f"), *GetName(), OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (MoveDirection*MoveDistance); // Final Location
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	} else {
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlatformVelocity*DeltaTime; // framerate independent
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime) {
	// UE_LOG(LogTemp, Display, TEXT("%s Rotating..."), *GetName());
	AddActorLocalRotation(RotationVelocity*DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(StartLocation, GetActorLocation());
}