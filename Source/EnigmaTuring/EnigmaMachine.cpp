// Fill out your copyright notice in the Description page of Project Settings.


#include "EnigmaMachine.h"
#include "RotorWheel.h"
int32 AEnigmaMachine::EncodeLetter(int32 AlphabetIndex)
{
	AlphabetIndex = FirstWheel->EncryptLetter(AlphabetIndex);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Letter:%c"), (TCHAR)(AlphabetIndex+'A')));
	return AlphabetIndex;
}

