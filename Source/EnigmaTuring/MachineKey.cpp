// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineKey.h"
#include "EnigmaMachine.h"
void AMachineKey::Interact()
{
	EnigmaMachine->EncodeLetter(Letter[0] - 'A');
}
