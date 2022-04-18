// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnigmaMachine.generated.h"

class ARotorWheel;

UCLASS()
class ENIGMATURING_API AEnigmaMachine : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditInstanceOnly)
	ARotorWheel* FirstWheel;

	int32 EncodeLetter(int32 AlphabetIndex);
};
