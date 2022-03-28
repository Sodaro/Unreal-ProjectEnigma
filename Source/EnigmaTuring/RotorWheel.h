// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "RotorWheel.generated.h"

UENUM(BlueprintType)
enum class Cipher : uint8 {
	EnigmaI = 0   UMETA(DisplayName = "EnigmaI"),
	EnigmaII = 1  UMETA(DisplayName = "EnigmaII"),
	EnigmaIII = 2 UMETA(DisplayName = "EnigmaIII"),
	ReflectorB = 3 UMETA(DisplayName = "ReflectorB")
};

UCLASS()
class ENIGMATURING_API ARotorWheel : public AInteractableObject
{
	GENERATED_BODY()

	TCHAR Alphabet[26] =
	{
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	TCHAR EnigmaI[26] =
	{
		'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'
	};
	TCHAR EnigmaII[26] =
	{
		'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'
	};
	TCHAR EnigmaIII[26] =
	{
		'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'
	};
	TCHAR ReflectorB[26] =
	{
		'Y','R','U','H','Q','S','L','D','P','X','N','G','O','K','M','I','E','B','F','Z','C','W','V','J','A','T'
	};
	TCHAR* ActiveArr;
	int CurrentLetterIndex = 0;
	int Offset = 0;

	TCHAR NotchPos = 'Q';

	FString DisplayedText = "A";
protected:
	virtual void BeginPlay() override;
public:
	ARotorWheel();

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	Cipher Type;

	UPROPERTY(EditAnywhere)
	ARotorWheel* PrevWheel;

	UPROPERTY(EditAnywhere)
	ARotorWheel* NextWheel;

	virtual void Interact() override;
	void Rotate();
	void Encode(int alphabetIndex, bool reverse);
};
