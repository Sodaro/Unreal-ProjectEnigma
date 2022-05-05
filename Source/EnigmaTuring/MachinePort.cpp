// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePort.h"

#include "MachineCable.h"

TWeakObjectPtr<AMachinePort> AMachinePort::GetSwappedPort()
{
	if (ConnectedCable == nullptr)
		return nullptr;

	return ConnectedCable->GetSwappedPort(this);
}

