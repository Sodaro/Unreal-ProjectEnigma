// Fill out your copyright notice in the Description page of Project Settings.


#include "RotorWheel.h"
#include <Components/TextRenderComponent.h>
ARotorWheel::ARotorWheel()
{

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	Text->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARotorWheel::BeginPlay()
{
	Super::BeginPlay();
	Text->Text = FText::FromString(DisplayedText);

	switch (Type)
	{
	case Cipher::EnigmaI:
		ActiveArr = EnigmaI;
		NotchPos = 'Q';
		break;
	case Cipher::EnigmaII:
		ActiveArr = EnigmaII;
		NotchPos = 'E';
		break;
	case Cipher::EnigmaIII:
		ActiveArr = EnigmaIII;
		NotchPos = 'V';
		break;
	case Cipher::ReflectorB:
		ActiveArr = ReflectorB;
		NotchPos = ' ';
		break;
	}
}

void ARotorWheel::Interact()
{
	Super::Interact();
	Rotate();
}

void ARotorWheel::Rotate()
{
	TCHAR old = Alphabet[Offset];
	++Offset %= 26;
	float amount = 360.f / 26;
	//++CurrentLetterIndex %= 26;
	//if (NextWheel != nullptr && old == NotchPos)
	//	NextWheel->Rotate();
	
	//DisplayedText = "";
	//DisplayedText = DisplayedText.AppendChar(Alphabet[CurrentLetterIndex]);
	FQuat rotation = FQuat::MakeFromEuler(FVector{ 0, amount, 0 });
	Mesh->AddRelativeRotation(rotation);
	Text->SetText(FText::FromString(DisplayedText));

	Encode(0, false);
}

void ARotorWheel::Encode(int alphabetIndex, bool reverse)
{
	int cipherLetterIndex = (alphabetIndex + Offset) % 26;
	TCHAR letter = ActiveArr[cipherLetterIndex];

	alphabetIndex = letter - 'A';

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Letter:%c"), Alphabet[alphabetIndex - Offset]));
	alphabetIndex -= Offset;
	if (alphabetIndex < 0)
		alphabetIndex += 26;
	if (NextWheel != nullptr && reverse == false)
	{
		NextWheel->Encode(alphabetIndex, false);
	}
	else if (PrevWheel != nullptr)
	{
		PrevWheel->Encode(alphabetIndex, true);
	}
}
