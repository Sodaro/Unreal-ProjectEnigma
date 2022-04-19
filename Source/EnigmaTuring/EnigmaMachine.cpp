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

void AEnigmaMachine::PressKey(int32 AlphabetIndex)
{
	FString IndexKey = "";
	IndexKey = IndexKey.AppendChar((TCHAR)(AlphabetIndex + 'A'));
	KeyLampPairs[IndexKey].Key->PlayPressAnimation(0.25f);
}
int32 AEnigmaMachine::EncodeLetter(int32 AlphabetIndex)
{
	AlphabetIndex = FirstWheel->EncryptLetter(AlphabetIndex);
	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Letter:%c"), (TCHAR)(AlphabetIndex+'A')));
	
	if (LastLampKey != "")
	{
		KeyLampPairs[LastLampKey].Lamp->TurnOff();
	}
	LastLampKey.Reset();
	LastLampKey = LastLampKey.AppendChar((TCHAR)(AlphabetIndex + 'A'));
	KeyLampPairs[LastLampKey].Lamp->TurnOn();

	OutputText += (TCHAR)(AlphabetIndex + 'A');
	
	FString ReadableText = "";
	ReadableText += OutputText[0];
	for (int i = 1; i < OutputText.Len(); i++)
	{
		if (i % 5 == 0)
			ReadableText += " ";

		ReadableText += OutputText[i];
	}

	OutputWidget->SetText(ReadableText);
	return AlphabetIndex;
}

