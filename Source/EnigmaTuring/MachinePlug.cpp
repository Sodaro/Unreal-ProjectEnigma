// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePlug.h"
//
//void AMachinePlug::Interact()
//{
//
//}

void AMachinePlug::DisconnectPlug()
{
	ConnectedPlug = nullptr;
}

void AMachinePlug::ConnectPlug(TWeakObjectPtr<AMachinePlug> Plug)
{
	if (ConnectedPlug.IsValid())
		ConnectedPlug->DisconnectPlug();

	ConnectedPlug = Plug;
}
