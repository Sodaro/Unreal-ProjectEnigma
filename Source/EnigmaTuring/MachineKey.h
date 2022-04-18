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
	void Interact() override;

	UPROPERTY(EditInstanceOnly)
	AEnigmaMachine* EnigmaMachine;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetLetter() { return Letter; }

	UPROPERTY(EditInstanceOnly)
	FString Letter;
};
