// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePlug.h"

#include "MachineCable.h"
//
//void AMachinePlug::Interact()
//{
//
//}

bool AMachinePlug::HasConnectedPlug()
{
	if (ConnectedCable == nullptr)
		return false;

	if (ConnectedCable->StartMachinePlug == this)
		return ConnectedCable->EndMachinePlug != nullptr;
	else if (ConnectedCable->EndMachinePlug == this)
		return ConnectedCable->StartMachinePlug != nullptr;

	return false;
}

TWeakObjectPtr<AMachinePlug> AMachinePlug::GetConnectedPlug()
{
	if (ConnectedCable == nullptr)
		return nullptr;

	if (ConnectedCable->StartMachinePlug == this)
		return ConnectedCable->EndMachinePlug;
	else if (ConnectedCable->EndMachinePlug == this)
		return ConnectedCable->StartMachinePlug;

	return nullptr;
}

void AMachinePlug::DisconnectPlug()
{
	if (ConnectedCable == nullptr)
		return;

	if (ConnectedCable->StartMachinePlug == this)
		ConnectedCable->StartMachinePlug = nullptr;
	else if (ConnectedCable->EndMachinePlug == this)
		ConnectedCable->EndMachinePlug = nullptr;

	ConnectedCable = nullptr;
}

void AMachinePlug::ConnectPlug(TWeakObjectPtr<AMachinePlug> Plug)
{
	if (ConnectedPlug.IsValid())
		ConnectedPlug->DisconnectPlug();

	ConnectedPlug = Plug;
}
