// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "FirstGame.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerController.h"
#include "CountessSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "RotatingActor.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Enemy.h"
#include "Engine/SkeletalMeshSocket.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Just affect camera only!
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character movement configuration
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create and follow camera

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Health = 85.f;
	MaxHealth = 100.f;
	XP = 0;
	Damage = 10.f;
}

void AMainCharacter::SetHealth(float Amount)
{
	if (Amount > MaxHealth)
	{
		Health = MaxHealth;
	}
	else if (Amount < 0)
	{
		Health = 0;
	}
	else 
	{
		Health = Amount;
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerController = Cast<AMainPlayerController>(GetController());

	UE_LOG(CountessLog, VeryVerbose, TEXT("CountessLog VeryVerbose"));
	UE_LOG(CountessLog, Verbose, TEXT("CountessLog Verbose"));
	UE_LOG(CountessLog, Warning, TEXT("CountessLog Warning"));
	UE_LOG(CountessLog, Display, TEXT("CountessLog Display"));
	UE_LOG(CountessLog, Log, TEXT("CountessLog Log"));
	UE_LOG(CountessLog, Error, TEXT("CountessLog Error"));
	//UE_LOG(CountessLog, Fatal, TEXT("CountessLog Fatal - This will crash the game!!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Blue, TEXT("Printing a message to the screen!"), false);
	}

	print("Use of print macro");
	print_k(2, "You'll only see one of these print_k messages!");
	print_k(2, "You'll only see one of these print_k messages!");

	printf("Formatting the string with the Actor Name: %s", *GetName());

	TSubclassOf<AActor> WorldClassObject = ARotatingActor::StaticClass();
	TArray<AActor*> ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, ActorsOfClass);
	if (ActorsOfClass.Num() > 0)
	{
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), ActorsOfClass[0]);
		if (NavPath->PathPoints.Num() > 0)
		{
			for (auto pt : NavPath->PathPoints)
			{
				DrawDebugSphere(GetWorld(), pt, 20.f, 12, FColor::Green, true);
			}
		}
	}
}

void AMainCharacter::MoveForward(float Value)
{

	if ((Controller != NULL) && (Value != 0.0f) && !bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !bDead)
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get the right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement in direction
		AddMovementInput(Direction, Value);
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		printf_k(1, "DeltaTime: %f", DeltaTime);
	}

	DrawDebugPoint(GetWorld(), GetActorLocation() + FVector(0.f, 0.f, 50.f), 5.f, FColor::Blue, false, 3.f);
	DrawDebugLine(GetWorld(), FVector(0.f, 0.f, 400.f), GetActorLocation(), FColor::Red, false, -1.f);

	FHitResult HitResult;
	FVector Start = GetActorLocation() + FVector(0.f, 0.f, 75.f);
	FVector End = Start + GetActorForwardVector() * 500.f;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	//GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionQueryParams);

	//TArray<FHitResult> HitResults;
	//GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECollisionChannel::ECC_Visibility);
	/**for (int32 i = 0; i < HitResults.Num(); i++)
	{
		AActor* HitActor = HitResults[i].GetActor();

		if (HitActor)
		{
			FString ActorName = HitActor->GetName();
			printf_k(i, "%d ActorName: %s", i, *ActorName);
		}
		else
		{
			printf_k(i, "%d Failed Hit!", i);
		}
	}
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.Location, 15.f, 12, FColor::Red, false, 5.f);
	}*/

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult BoxTraceResult;
	UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), Start, End, FVector(32.f, 32.f, 32.f), FRotator(), ObjectTypes,
		true, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, BoxTraceResult, true, FColor::Red, FColor::Blue);
	if (BoxTraceResult.bBlockingHit)
	{
		printf_k(1, "Blocking Hit!");
	}
}

void AMainCharacter::LMBDown() 
{
	if (bAttacking || bDead) return;

	bAttacking = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CountessAttackMontage)
	{
		AnimInstance->Montage_Play(CountessAttackMontage);
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LMBDown", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMainCharacter::ESCDown);
}

void AMainCharacter::ESCDown()
{
	if (MainPlayerController)
	{
		MainPlayerController->TogglePauseMenu();
	}
}

void AMainCharacter::SaveGame()
{
	UCountessSaveGame* SaveGameInstance = Cast<UCountessSaveGame>(UGameplayStatics::CreateSaveGameObject(UCountessSaveGame::StaticClass()));
	SaveGameInstance->Health = Health;
	SaveGameInstance->MaxHealth = MaxHealth;

	SaveGameInstance->WorldLocation = GetActorLocation();
	SaveGameInstance->WorldRotation = GetActorRotation();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerName, SaveGameInstance->UserSlot);
}

void AMainCharacter::LoadGame()
{
	UCountessSaveGame* LoadGameInstance = Cast<UCountessSaveGame>(UGameplayStatics::CreateSaveGameObject(UCountessSaveGame::StaticClass()));
	LoadGameInstance = Cast<UCountessSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserSlot));

	Health = LoadGameInstance->Health;
	MaxHealth = LoadGameInstance->MaxHealth;

	SetActorLocation(LoadGameInstance->WorldLocation);
	SetActorRotation(LoadGameInstance->WorldRotation);
}

void AMainCharacter::ToggleAllRotators()
{
	/**TSubclassOf<AActor> WorldClassObject = ARotatingActor::StaticClass();
	TArray<AActor*> ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, ActorsOfClass);

	for (AActor* Actor : ActorsOfClass)
	{
		ARotatingActor* RotatingActor = Cast<ARotatingActor>(Actor);

		if (RotatingActor)
		{
			RotatingActor->ToggleRotate();
		}
	}*/

	RotateDelegate.ExecuteIfBound();

}

void AMainCharacter::SwordBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy)
		{
			if (Enemy->HitParticles)
			{
				const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponBladeLSocket");

				if (WeaponSocket)
				{
					FVector SocketLocation = WeaponSocket->GetSocketLocation(GetMesh());

					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticles, SocketLocation, FRotator(0.f), false);
				}
			}
			if (Enemy->HitSound)
			{
				UGameplayStatics::PlaySound2D(this, Enemy->HitSound);
			}
			if (DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(Enemy, Damage, GetController(), this, DamageTypeClass);
			}
		}
	}
}

void AMainCharacter::DeathEnd()
{
	UKismetSystemLibrary::QuitGame(this, Cast<APlayerController>(GetController()), EQuitPreference::Quit, true);
}
