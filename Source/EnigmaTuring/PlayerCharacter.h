// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"
class UCameraComponent;
class AEnigmaMachine;
class AInteractableObject;

UCLASS()
class ENIGMATURING_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

	void Interact();
	void EncodeLetter(FKey Key);

	void DoTrace();

	bool LoggingEnabled = true;
public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ToggleScreenLogging();

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float MinAngle = -60.f;

	UPROPERTY(EditAnywhere)
	float MaxAngle = 60.f;

	UPROPERTY(EditInstanceOnly)
	AEnigmaMachine* EnigmaMachine;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	TWeakObjectPtr<AInteractableObject> HoveredInteractable;

};
