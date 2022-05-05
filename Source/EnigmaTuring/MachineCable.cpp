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
	StartPlug->Cable = this;

	EndPlug = (AMachineCablePlug*)(GetWorld()->SpawnActor(EndPieceClass, &Location));
	EndPlug->SetActorLocation(Location + FVector{ 0,50,0 });
	EndPlug->Cable = this;

	CableComp->SetAttachEndTo(EndPlug, EndPlug->GetDefaultAttachComponent()->GetAttachSocketName());
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
		CableComp->CableLength = FVector::Dist(Location, EndPlug->GetActorLocation()) + 10.f;
	}
	
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

AMachinePort* AMachineCable::GetSwappedPort(AMachinePort* InPort) const
{
	if (InPort == nullptr)
		return nullptr;

	//if 1 return 2, if 2 return 1
	if (StartPlug->OverlappedPort == InPort)
	{
		return EndPlug->OverlappedPort;
	}
	else
	{
		return StartPlug->OverlappedPort;
	}
}
