// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"
class UCameraComponent;
class UStaticMeshComponent;
class ARotorWheel;

UCLASS()
class ENIGMATURING_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

	void Interact();
	void EncodeLetter(FKey Key);
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

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float MinAngle = -60.f;

	UPROPERTY(EditAnywhere)
	float MaxAngle = 60.f;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly)
	ARotorWheel* FirstWheel;

	UCameraComponent* Camera;

};
