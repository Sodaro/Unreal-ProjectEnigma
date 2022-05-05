// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePort.h"

#include "MachineCable.h"
//
//void AMachinePlug::Interact()
//{
//
//}

bool AMachinePort::HasConnectedPort()
{
	if (ConnectedCable == nullptr)
		return false;

	if (ConnectedCable->StartMachinePort == this)
		return ConnectedCable->EndMachinePort != nullptr;
	else if (ConnectedCable->EndMachinePort == this)
		return ConnectedCable->StartMachinePort != nullptr;

	return false;
}

TWeakObjectPtr<AMachinePort> AMachinePort::GetConnectedPort()
{
	if (ConnectedCable == nullptr)
		return nullptr;

	if (ConnectedCable->StartMachinePort == this)
		return ConnectedCable->EndMachinePort;
	else if (ConnectedCable->EndMachinePort == this)
		return ConnectedCable->StartMachinePort;

	return nullptr;
}

void AMachinePort::DisconnectPlug()
{
	if (ConnectedCable == nullptr)
		return;

	if (ConnectedCable->StartMachinePort == this)
		ConnectedCable->StartMachinePort = nullptr;
	else if (ConnectedCable->EndMachinePort == this)
		ConnectedCable->EndMachinePort = nullptr;

	ConnectedCable = nullptr;
}

void AMachinePort::ConnectPlug(TWeakObjectPtr<AMachinePort> Port)
{
	if (ConnectedCable == nullptr)
		return;

	if (ConnectedCable->StartMachinePort == this)
		ConnectedCable->StartMachinePort = nullptr;
	else if (ConnectedCable->EndMachinePort == this)
		ConnectedCable->EndMachinePort = nullptr;
}
