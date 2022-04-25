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
	/*
	* Plugboard is not implemented but would provide extra layer of encryption
	* before any other encryption has happened and after the regular encryption
	* is done.
	*/

	/*
	* ENCRYPTION LOGIC
	* 1. Rotate first wheel every time a key is pressed.
	* 2. Encrypt the input based on each wheel's configs.
	* 3. Get the connected letter in the reflector.
	* 4. Reverse through the wheels. 
		(different encryption to simulate the electric signal going the opposite way)
	* 5. Turn on the lamp matching the encrypted key, and output it to the textbox.
	*/

	RotorWheels[0]->Rotate();

	TCHAR Letter;
	for (int i = 0; i < 3; i++)
	{
		AlphabetIndex = RotorWheels[i]->Encode(AlphabetIndex, false);
		Letter = (TCHAR)(AlphabetIndex + 'A');
	}

	AlphabetIndex = ReflectorWheel->Encode(AlphabetIndex, false);
	Letter = (TCHAR)(AlphabetIndex + 'A');

	for (int i = 2; i >= 0; i--)
	{
		AlphabetIndex = RotorWheels[i]->Encode(AlphabetIndex, true);
		Letter = (TCHAR)(AlphabetIndex + 'A');
	}
	
	if (LastLampKey != "")
	{
		KeyLampPairs[LastLampKey].Lamp->TurnOff();
	}

	LastLampKey.Reset();
	LastLampKey = LastLampKey.AppendChar(Letter);
	KeyLampPairs[LastLampKey].Lamp->TurnOn();

	FString ReadableText = "";
	OutputText += Letter;
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

