// Fill out your copyright notice in the Description page of Project Settings.


#include "EnigmaMachine.h"
#include "RotorWheel.h"
#include "MachineKey.h"
#include "MachineLamp.h"
#include "MachineTextOutput.h"

void AEnigmaMachine::BeginPlay()
{
	OutputWidget = NewObject<UMachineTextOutput>(this, OutputWidgetClass);
	OutputWidget->AddToViewport();
}

void AEnigmaMachine::ChangeRingOffset(RingPosition RingPos, int32 Offset)
{
	if (Offset > 25)
		Offset = 25;
	else if (Offset < 0)
		Offset = 0;

	switch (RingPos)
	{
	case RingPosition::LEFT:
		LeftWheel->RingSettingOffset = Offset;
		break;
	case RingPosition::MID:
		MidWheel->RingSettingOffset = Offset;
		break;
	case RingPosition::RIGHT:
		RightWheel->RingSettingOffset = Offset;
		break;
	default:
		break;
	}
}

void AEnigmaMachine::SetRingPosition(RingPosition RingPos, int32 Position)
{
	if (Position > 25)
		Position = 25;
	else if (Position < 0)
		Position = 0;

	switch (RingPos)
	{
	case RingPosition::LEFT:
		LeftWheel->SetRingRotationOffset(Position);
		break;
	case RingPosition::MID:
		MidWheel->SetRingRotationOffset(Position);
		break;
	case RingPosition::RIGHT:
		RightWheel->SetRingRotationOffset(Position);
		break;
	default:
		break;
	}
}

void AEnigmaMachine::PressKey(int32 AlphabetIndex)
{
	FString IndexKey = "";
	IndexKey = IndexKey.AppendChar((TCHAR)(AlphabetIndex + 'A'));
	KeyLampPairs[IndexKey].Key->PlayPressAnimation(0.25f);
}
int32 AEnigmaMachine::EncodeLetter(int32 InAlphabetIndex)
{
	int32 OutAlphabetIndex;

	RightWheel->Rotate();
	/*PLUGBOARD(INALPHABETINDEX)*/
	OutAlphabetIndex = RightWheel->Encode(InAlphabetIndex, false);
	TCHAR Letter = (TCHAR)(OutAlphabetIndex + 'A');

	OutAlphabetIndex = MidWheel->Encode(OutAlphabetIndex, false);
	Letter = (TCHAR)(OutAlphabetIndex + 'A');

	OutAlphabetIndex = LeftWheel->Encode(OutAlphabetIndex, false);
	Letter = (TCHAR)(OutAlphabetIndex + 'A');

	OutAlphabetIndex = ReflectorWheel->Encode(OutAlphabetIndex, false);
	Letter = (TCHAR)(OutAlphabetIndex + 'A');

	OutAlphabetIndex = LeftWheel->Encode(OutAlphabetIndex, true);
	Letter = (TCHAR)(OutAlphabetIndex + 'A');

	OutAlphabetIndex = MidWheel->Encode(OutAlphabetIndex, true);
	Letter = (TCHAR)(OutAlphabetIndex + 'A');

	OutAlphabetIndex = RightWheel->Encode(OutAlphabetIndex, true);
	Letter = (TCHAR)(OutAlphabetIndex + 'A');

	/*PLUGBOARD(OutAlphabetIndex)*/
	if (LastLampKey != "")
	{
		KeyLampPairs[LastLampKey].Lamp->TurnOff();
	}
	LastLampKey.Reset();
	LastLampKey = LastLampKey.AppendChar((TCHAR)(OutAlphabetIndex + 'A'));
	KeyLampPairs[LastLampKey].Lamp->TurnOn();

	OutputText += Letter;

	FString ReadableText = "";
	ReadableText += OutputText[0];
	for (int i = 1; i < OutputText.Len(); i++)
	{
		if (i % 5 == 0)
			ReadableText += " ";

		ReadableText += OutputText[i];
	}

	OutputWidget->SetText(ReadableText);
	
	return OutAlphabetIndex;
}

