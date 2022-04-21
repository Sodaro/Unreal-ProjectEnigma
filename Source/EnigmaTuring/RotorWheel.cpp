// Fill out your copyright notice in the Description page of Project Settings.


#include "RotorWheel.h"
#include <Components/TextRenderComponent.h>
ARotorWheel::ARotorWheel()
{
	//Super::Interact();
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
	//++RingSettingOffset %= 26;
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
	//Encode(0, false);
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

int32 ARotorWheel::Encode(int32 Input, bool reverse)
{
	int32 Index, NewAlphabetIndex;
	TCHAR InputLetter, CipherLetter;


	InputLetter = Alphabet[Input];
	if (reverse == false)
	{
		Index = Input + CurrentRotationOffset - RingSettingOffset;
		if (Index < 0)
			Index += 26;
		else if (Index >= 26)
			Index -= 26;
		CipherLetter = ActiveArr[Index];
		NewAlphabetIndex = CipherLetter - 'A' - CurrentRotationOffset + RingSettingOffset;
		if (NewAlphabetIndex < 0)
			NewAlphabetIndex += 26;
		else if (NewAlphabetIndex >= 26)
			NewAlphabetIndex -= 26;
	}
	else if (reverse == true)
	{
		Index = Input + CurrentRotationOffset - RingSettingOffset;
		if (Index < 0)
			Index += 26;
		else if (Index >= 26)
			Index -= 26;
		for (int i = 0; i < 26; i++)
		{
			if (ActiveArr[i] - 'A' == Index)
			{
				NewAlphabetIndex = i - CurrentRotationOffset + RingSettingOffset;
				if (NewAlphabetIndex < 0)
					NewAlphabetIndex += 26;
				else if (NewAlphabetIndex >= 26)
					NewAlphabetIndex -= 26;
				break;
			}
		}
	}

	return NewAlphabetIndex;


	//if (reverse == true)
	//{
	//	//CipherLetter = Z = 25, ActiveArr[25] == E
	//	NewAlphabetIndex = ActiveArr[NewAlphabetIndex] - 'A';
	//}
	////else
	////{
	////	//Z = 25, ActiveArr[25] == E

	////	CipherLetter = ActiveArr[NewAlphabetIndex];
	////	//for (int i = 0; i < 26; i++)
	////	//{
	////	//	if (ActiveArr[i] == CipherLetter)
	////	//	{
	////	//		NewAlphabetIndex = i;
	////	//		break;
	////	//	}
	////	//}
	////}
	//if (NextWheel != nullptr && reverse == false)
	//{
	//	Input = NextWheel->Encode(NewAlphabetIndex, false);
	//}
	//else if (PrevWheel != nullptr)
	//{
	//	Input = PrevWheel->Encode(NewAlphabetIndex, true);
	//}
	//Input -= CurrentRotationOffset;
	//if (Input < 0)
	//	Input += 26;
	//return ActiveArr[Input]-'A';
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

void ARotorWheel::ShiftLeft()
{
	int temp = ActiveArr[0];

	for (int i = 0; i < 26; i++)
	{
		ActiveArr[i] = ActiveArr[i + 1];
	}
	ActiveArr[25] = temp;
}

int32 ARotorWheel::IncrementRingOffset()
{
	++CurrentRotationOffset %= 26;
	ChangeDisplayName();
	return CurrentRotationOffset;
}

int32 ARotorWheel::IncrementRingSettingPosition()
{
	++RingSettingOffset %= 26;
	//ShiftLeft();
	return RingSettingOffset;
}
