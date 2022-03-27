// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "RotorWheel.generated.h"

/**
 * 
 */
UCLASS()
class ENIGMATURING_API ARotorWheel : public AInteractableObject
{
	GENERATED_BODY()

	TCHAR LetterArr[26] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	int CurrentLetterIndex = 0;

	FString DisplayedText = "A";
protected:
	virtual void BeginPlay() override;
public:
	ARotorWheel();

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	ARotorWheel* NextWheel;

	virtual void Interact() override;

};
