// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineCablePlug.h"
#include "MachineCable.h"
#include "Components/BoxComponent.h"
#include "MachinePort.h"
AMachineCablePlug::AMachineCablePlug()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMachineCablePlug::HandleOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AMachineCablePlug::HandleEndOverlap);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollider->SetBoxExtent(BoxExtents, true);
}
//
//TWeakObjectPtr<AMachinePort> AMachineCablePlug::GetSwappedPort() const
//{
//	return Cable->GetSwappedPort(OverlappedPort);
//}

void AMachineCablePlug::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("OverlapBegin"));
	if (AMachinePort* Port = Cast<AMachinePort>(OtherActor))
	{
		OverlappedPort = Port;
		OverlappedPort->ConnectedCable = Cable;
	}
}

void AMachineCablePlug::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("OverlapEnd"));
	if (AMachinePort* Port = Cast<AMachinePort>(OtherActor))
	{
		if (Port == OverlappedPort)
			OverlappedPort = nullptr;
	}
}
