// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "InteractableObject.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 180.f));
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (GEngine)
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("x,y: %f %f"), horizontal, vertical));
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
	
}

void APlayerCharacter::Interact()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("click")));

	FHitResult hit;
	FVector startPos = Camera->GetComponentLocation();
	FVector endPos = startPos + Camera->GetForwardVector()*1000.f;


	UWorld* world = GetWorld();
	UKismetSystemLibrary::DrawDebugLine(world, startPos, endPos, FColor::Magenta, 10.f, 2.f);

	world->LineTraceSingleByChannel(hit, startPos, endPos, ECC_WorldStatic);
	if (hit.bBlockingHit)
	{
		if (hit.Actor.IsValid() == false)
			return;

		if (hit.Actor.Get()->IsA<AInteractableObject>())
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("hit:" + hit.Actor.Get()->GetName()));

			FLinearColor color;
			switch (ColorIndex)
			{
			case 0:
				color = FLinearColor::Blue;
				break;
			case 1:
				color = FLinearColor::Yellow;
				
				break;
			case 2:
				color = FLinearColor::Green;
				break;
			case 3:
				color = FLinearColor::Red;
				break;
			}
			++ColorIndex %= 4;
			Cast<AInteractableObject>(hit.Actor)->ChangeColor(color);
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::Interact);
	InputComponent->BindAxis("Look X");
	InputComponent->BindAxis("Look Y");
}
