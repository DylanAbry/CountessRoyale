// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FirstPawn.generated.h"

UCLASS()
class FIRSTGAME_API AFirstPawn : public APawn
{
	GENERATED_BODY()

	// Mesh component to give pawn a visual representation in the world

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

	// Camera boom positioning camera behind the pawn

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow camera

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	AFirstPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void E_KeyPressed();
	void E_KeyReleased();
	void Shift_Key(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement") float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement") FVector2D Direction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
