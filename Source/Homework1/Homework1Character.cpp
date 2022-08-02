// Copyright Epic Games, Inc. All Rights Reserved.

#include "Homework1Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Homework1GameMode.h"
//////////////////////////////////////////////////////////////////////////
// AHomework1Character

AHomework1Character::AHomework1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement =
		true;  // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate =
		FRotator(0.0f, 540.0f, 0.0f);  // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength =
		300.0f;  // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation =
		true;  // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(
		CameraBoom,
		USpringArmComponent::SocketName);  // Attach the camera to the end of the
										   // boom and let the boom adjust to
										   // match the controller orientation
	FollowCamera->bUsePawnControlRotation =
		false;  // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component
	// (inherited from Character) are set in the derived blueprint asset named
	// MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHomework1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this,
		&ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this,
		&AHomework1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,
		&AHomework1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of
	// devices differently "turn" handles devices that provide an absolute delta,
	// such as a mouse. "turnrate" is for devices that we choose to treat as a
	// rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this,
		&AHomework1Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this,
		&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this,
		&AHomework1Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this,
		&AHomework1Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this,
		&AHomework1Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this,
		&AHomework1Character::OnResetVR);
}

void AHomework1Character::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACoin* coin = Cast<ACoin>(OtherActor);
	if (coin != nullptr) {
		AddCoinNumber(coin->CoinType);
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
		GI->MySaveGame();
		coin->Destroy();
	}
}

void AHomework1Character::BeginPlay()
{
	Super::BeginPlay();
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GameInstance->CharacterInit(this);
}

void AHomework1Character::Destroyed()
{
	Super::Destroyed();
	if (UWorld* world = GetWorld())
	{
		if (AHomework1GameMode* GameMode = Cast<AHomework1GameMode>(world->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void AHomework1Character::CallRestartPlayer()
{
	AController* ControllerRef = GetController();
	Destroy();
	if (UWorld* World = GetWorld())
	{
		if (AHomework1GameMode* GameMode = Cast<AHomework1GameMode>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(ControllerRef);
		}
	}
}

void AHomework1Character::AddCoinNumber(ECoinType CoinType)
{
	if (CoinType == ECoinType::Copper) {
		m_CopperCoinNumber++;
	}
	else if (CoinType == ECoinType::Silver) {
		m_SilverCoinNumber++;
	}
	else if (CoinType == ECoinType::Gold) {
		m_GoldCoinNumber++;
	}
}

int AHomework1Character::GetCoinNumber(ECoinType CoinType)
{
	if (CoinType == ECoinType::Copper) {
		return m_CopperCoinNumber;
	}
	else if (CoinType == ECoinType::Silver) {
		return m_SilverCoinNumber;
	}
	else if (CoinType == ECoinType::Gold) {
		return m_GoldCoinNumber;
	}
	return m_CopperCoinNumber;
}

void AHomework1Character::OnResetVR()
{
	// If Homework1 is added to a project via 'Add Feature' in the Unreal Editor
	// the dependency on HeadMountedDisplay in Homework1.Build.cs is not
	// automatically propagated and a linker error will result. You will need to
	// either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs
	// PublicDependencyModuleNames in order to build successfully (appropriate if
	// supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below
	//(appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHomework1Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AHomework1Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AHomework1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHomework1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate *
		GetWorld()->GetDeltaSeconds());
}

void AHomework1Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHomework1Character::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
