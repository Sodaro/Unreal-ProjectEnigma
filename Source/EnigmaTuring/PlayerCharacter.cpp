#include "PlayerCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "InteractableObject.h"
#include "EnigmaMachine.h"
#include "Kismet/GameplayStatics.h"
#include "MachinePort.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(CameraRelativeStandPos);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::DoTrace()
{
	FHitResult HitResult;
	FVector StartPos = Camera->GetComponentLocation();
	FVector EndPos = StartPos + Camera->GetForwardVector() * 5000.f;

	UWorld* world = GetWorld();

	world->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECC_WorldStatic);
	if (HitResult.bBlockingHit)
	{
		if (HitResult.Actor.IsValid() == false)
			return;

		if (HitResult.Actor.Get()->IsA<AInteractableObject>())
		{
			HoveredInteractable = Cast<AInteractableObject>(HitResult.Actor);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float horizontal = InputComponent->GetAxisValue("Look X");
	float vertical = InputComponent->GetAxisValue("Look Y");

	//rotate player
	FQuat rotQuatPlayer = FQuat::MakeFromEuler({0,0,horizontal * DeltaTime * RotationSpeed});
	SetActorRotation(GetActorRotation().Quaternion() * rotQuatPlayer);

	//rotate camera
	FQuat rotQuatCamera = FQuat::MakeFromEuler({ 0,vertical * DeltaTime * RotationSpeed,0 });
	FQuat cameraRot = Camera->GetRelativeRotation().Quaternion();
	FVector cameraEuler = cameraRot.Euler();
	if ((cameraEuler.Y < MaxAngle && vertical > 0) || (cameraEuler.Y > MinAngle && vertical < 0))
	{
		Camera->SetRelativeRotation(cameraRot* rotQuatCamera);
	}

	DoTrace();
	if (HoveredInteractable.IsValid())
	{
		HoveredInteractable->Hover();
	}
}

void APlayerCharacter::Interact()
{
	if (HoveredInteractable.IsValid() == false)
	{
		return;
	}

	HoveredInteractable->Interact();
	if (HoveredInteractable->IsA<AMachinePort>() == false)
	{
		return;
	}

	AMachinePort* ClickedPlug = Cast<AMachinePort>(HoveredInteractable);
	if (HeldPlug == nullptr)
		HeldPlug = ClickedPlug;
	else
	{
		HeldPlug->ConnectPlug(ClickedPlug);
		ClickedPlug->ConnectPlug(HeldPlug);
	}
}

void APlayerCharacter::EncodeLetter(FKey Key)
{
	//Send the keyboard input to the enigma machine, given a key value of A-Z
	FString KeyName = Key.GetFName().ToString();
	if (KeyName.Len() > 1)
		return;

	TCHAR Letter = KeyName[0];
	int32 Value = Letter - 'A';
	if (Value >= 0 && Value <= 25)
	{
		EnigmaMachine->PressKey(Value);
		EnigmaMachine->EncodeLetter(Value);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::Interact);
	InputComponent->BindAxis("Look X");
	InputComponent->BindAxis("Look Y");
	InputComponent->BindAction("AnyKey", IE_Pressed, this, &APlayerCharacter::EncodeLetter);
	InputComponent->BindAction("ToggleLogging", IE_Pressed, this, &APlayerCharacter::ToggleScreenLogging);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::UnCrouch);
}

void APlayerCharacter::ToggleScreenLogging()
{
	LoggingEnabled = !LoggingEnabled;
	FString Cmd = LoggingEnabled ? "ENABLEALLSCREENMESSAGES" : "DISABLEALLSCREENMESSAGES";
	auto CoolController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CoolController->ConsoleCommand(Cmd, true);
}

void APlayerCharacter::Crouch()
{
	Camera->SetRelativeLocation(CameraRelativeCrouchPos);
}

void APlayerCharacter::UnCrouch()
{
	Camera->SetRelativeLocation(CameraRelativeStandPos);
}
