// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "MachineKey.generated.h"

/**
 * 
 */

class AEnigmaMachine;

UCLASS()
class ENIGMATURING_API AMachineKey : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Interact() override;
	AMachineKey();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector StartPosition;

	UPROPERTY(EditAnywhere)
	FVector EndPosition;

	UPROPERTY(EditInstanceOnly)
	AEnigmaMachine* EnigmaMachine;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetLetter() { return Letter; }

	UFUNCTION(BlueprintCallable)
	void PlayPressAnimation(float Duration);

	float PressTimer = 0.f;
	float PressDuration = 1.f;
	bool IsPressed = false;

	UPROPERTY(EditInstanceOnly)
	FString Letter;
};
