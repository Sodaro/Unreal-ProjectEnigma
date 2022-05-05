// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineCable.h"
#include "CableComponent.h"
#include "CableEndPiece.h"

// Sets default values
AMachineCable::AMachineCable()
{
	CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("CableComponent"));
	CableComp->SetupAttachment(RootComponent);
}

void AMachineCable::BeginPlay()
{
	StartPlug = NewObject<ACablePlug>(this, EndPieceClass);
	//StartPlug->OnInteract.BindSP(this, &AMachineCable::ConnectCable);

	EndPlug = NewObject<ACablePlug>(this, EndPieceClass);
	//EndPlug->OnInteract.BindSP(this, &AMachineCable::ConnectCable);
}

void AMachineCable::ConnectCable(AInteractableObject* Plug)
{
	if (ACablePlug* CablePlug = Cast<ACablePlug>(Plug))
	{
		if (CablePlug == Plug)
		{

		}
		else
		{

		}
	}
}

void AMachineCable::DisconnectCable(AInteractableObject* EndPiece)
{
}
