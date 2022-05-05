// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MachineCable.generated.h"

class UCableComponent;
class AMachinePort;
class AMachineCablePlug;
class AInteractableObject;

UCLASS()
class ENIGMATURING_API AMachineCable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMachineCable();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void ConnectCable(AInteractableObject* EndPiece);
	void DisconnectCable(AInteractableObject* EndPiece);

	UPROPERTY(EditDefaultsOnly)
	UCableComponent* CableComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMachineCablePlug> EndPieceClass;

	UPROPERTY()
	AMachinePort* StartMachinePort = nullptr;
	
	UPROPERTY()
	AMachineCablePlug* StartPlug = nullptr;

	UPROPERTY()
	AMachinePort* EndMachinePort = nullptr;

	UPROPERTY()
	AMachineCablePlug* EndPlug = nullptr;
};
