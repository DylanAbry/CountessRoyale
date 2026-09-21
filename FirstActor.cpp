// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFirstActor::AFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstActorMeshComp"));
	SetRootComponent(FirstActorMesh);
	ActorLifetime = 0.0f;
	ActorLevel = 0;

}

// Called when the game starts or when spawned
void AFirstActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s has been created successfully muthafucka!"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Do you seriously rerun the editor every time you compile???"), *GetName());
}


// Called every frame
void AFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);
	ActorLifetime += DeltaTime;

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("%s Location: (%f, %f, %f), Rotation: (%f, %f, %f)"), *GetName(), Location.X, Location.Y, Location.Z
		, Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
	Location.Z += 15.f * DeltaTime;
	Rotation.Yaw += 45.5 * DeltaTime;
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	*/
}

void AFirstActor::CheckLifetime()
{
	ActorLevel = ActorLifetime;
}

