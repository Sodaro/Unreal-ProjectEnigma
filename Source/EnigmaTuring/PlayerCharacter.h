// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class ENIGMATURING_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

	void Interact();
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


	//void HandleRotation(FVector vector);

	int ColorIndex = 0;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float MinAngle = -60.f;

	UPROPERTY(EditAnywhere)
	float MaxAngle = 60.f;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UCameraComponent* Camera;

};
