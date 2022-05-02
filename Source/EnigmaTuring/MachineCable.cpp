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
	StartCableEndPiece->OnInteract.BindSP(this, &AMachineCable::ConnectCable);
}

void AMachineCable::ConnectCable(AInteractableObject* EndPiece)
{
	if (ACableEndPiece* CablePiece = Cast<ACableEndPiece>(EndPiece))
	{
		if (CablePiece == StartCableEndPiece)
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
