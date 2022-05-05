// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineCable.h"
#include "CableComponent.h"
#include "MachineCablePlug.h"
// Sets default values
AMachineCable::AMachineCable()
{
	CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("CableComponent"));
	CableComp->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMachineCable::BeginPlay()
{
	Super::BeginPlay();
	FVector Location = GetActorLocation();
	StartPlug = (AMachineCablePlug*)(GetWorld()->SpawnActor(EndPieceClass, &Location));
	//StartPlug->OnInteract.BindSP(this, &AMachineCable::ConnectCable);
	

	EndPlug = (AMachineCablePlug*)(GetWorld()->SpawnActor(EndPieceClass, &Location));
	EndPlug->SetActorLocation(Location + FVector{ 50,0,0 });
	CableComp->SetAttachEndTo(EndPlug, EndPlug->GetDefaultAttachComponent()->GetAttachSocketName());
	//EndPlug->OnInteract.BindSP(this, &AMachineCable::ConnectCable);
}

void AMachineCable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::White, TEXT("COOLTICK"));

	FVector Location = StartPlug->GetActorLocation();
	if (StartPlug != nullptr)
	{
		SetActorLocation(Location);
	}
	
	if (EndPlug != nullptr)
	{
		//FTransform Transform = GetTransform();
		//CableComp->EndLocation = EndPlug->GetActorLocation();
	}

	//CableComp->CableLength = CableComp->EndLocation.Size();
	
}

void AMachineCable::ConnectCable(AInteractableObject* Plug)
{
	//if (ACablePlug* CablePlug = Cast<ACablePlug>(Plug))
	//{
	//	if (StartPlug == nullptr)
	//	{
	//		StartPlug = CablePlug;
	//	}
	//	else
	//	{
	//		EndPlug = CablePlug;
	//	}
	//	
	//}
}

void AMachineCable::DisconnectCable(AInteractableObject* EndPiece)
{
}
