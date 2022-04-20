// Fill out your copyright notice in the Description page of Project Settings.


#include "RotorWheel.h"
#include <Components/TextRenderComponent.h>
ARotorWheel::ARotorWheel()
{
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	Text->SetupAttachment(RootComponent);
}

void ARotorWheel::ChangeDisplayName()
{
	DisplayedText.Reset();
	DisplayedText = DisplayedText.AppendChar((TCHAR)('A' + CurrentRotationOffset));
	Text->SetText(FText::FromString(DisplayedText));
}

void ARotorWheel::DoRotation()
{
	++CurrentRotationOffset %= 26;
	float Amount = 360.f / 26;
	FQuat Rotation = FQuat::MakeFromEuler(FVector{ 0, Amount, 0 });
	Mesh->AddRelativeRotation(Rotation);
	ChangeDisplayName();
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

//void ARotorWheel::Interact()
//{
//	Super::Interact();
//	Rotate();
//}

void ARotorWheel::Rotate()
{
	DoRotation();
	Encode(0, false);
	if (CurrentRotationOffset + 'A' == NotchPos)
	{
		NextWheel->Rotate();
	}
}

void ARotorWheel::Rotate(TCHAR Input)
{
	DoRotation();

	Encode(Input - 'A', false);
	if (CurrentRotationOffset + 'A' == NotchPos)
	{
		NextWheel->Rotate();
	}
}

int32 ARotorWheel::Encode(int AlphabetIndex, bool reverse)
{
	int CipherLetterIndex = (AlphabetIndex - RingSettingOffset + CurrentRotationOffset) % 26;
	TCHAR Letter = Alphabet[CipherLetterIndex];
	TCHAR CipherLetter = ActiveArr[CipherLetterIndex];
	
	if (reverse)
	{
		//TODO: make this not a loop, use pairs or dicts
		for (int i = 0; i < 26; i++)
		{
			if (ActiveArr[i] == Letter)
			{
				CipherLetter = Alphabet[i];
				break;
			}
		}
		
	}

	AlphabetIndex = CipherLetter - 'A' - CurrentRotationOffset + RingSettingOffset;
	
	//alphabetIndex -= Offset;
	if (AlphabetIndex < 0)
		AlphabetIndex += 26;

	if (NextWheel != nullptr && reverse == false)
	{
		AlphabetIndex = NextWheel->Encode(AlphabetIndex, false);
	}
	else if (PrevWheel != nullptr)
	{
		AlphabetIndex = PrevWheel->Encode(AlphabetIndex, true);
	}
	else
	{
		return AlphabetIndex;
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Letter:%c"), Alphabet[AlphabetIndex]));*/
	}
	return AlphabetIndex;
}

int32 ARotorWheel::EncryptLetter(int32 Index)
{
	DoRotation();

	int32 RetVal = Encode(Index, false);
	if (CurrentRotationOffset + 'A' == NotchPos)
	{
		NextWheel->Rotate();
	}
	return RetVal;
}

void ARotorWheel::SetRingRotationOffset(int32 Offset)
{
	if (Offset < 0)
		Offset = 0;
	else if (Offset >= 26)
		Offset = 25;

	CurrentRotationOffset = Offset;
	ChangeDisplayName();
}

void ARotorWheel::ChangeRingSettingPosition(int32 Position)
{
	if (Position < 0)
		Position = 0;
	else if (Position >= 26)
		Position = 25;

	RingSettingOffset = Position;
}

void ARotorWheel::IncrementRingOffset()
{
	++CurrentRotationOffset %= 26;
	ChangeDisplayName();
}

void ARotorWheel::IncrementRingSettingPosition()
{
	++RingSettingOffset %= 26;
}
