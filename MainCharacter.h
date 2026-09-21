// Fill out your copyright notice in the Description page of Project Settings.



// C++ Source\FirstGame\MainCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCharacter.generated.h"

// Use a non-UDelegate for C++ only callbacks:
DECLARE_DELEGATE(FRotateDelegate);

UCLASS()
class FIRSTGAME_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// Reference to Player Controller (forward declared class in cpp or header include as needed)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller", meta = (AllowPrivateAccess = "true"))
	class AMainPlayerController* MainPlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LMBDown();
	void ESCDown();

public:
	// Sets default values for this character's properties
	AMainCharacter();

	FORCEINLINE float GetHealth() { return Health; }
	void SetHealth(float Amount);
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE void SetMaxHealth(float Amount) { MaxHealth = Amount; }

	// Plain C++ delegate (non-UObject) for native callbacks
	FRotateDelegate RotateDelegate;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void ToggleAllRotators();

	virtual void SwordBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void DeathEnd() override;

	FORCEINLINE void AddXP(int32 AddedXP) { XP += AddedXP;  }
};
