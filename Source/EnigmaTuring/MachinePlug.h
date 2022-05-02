// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "MachinePlug.generated.h"

class AMachineCable;
/**
 * 
 */
UCLASS()
class ENIGMATURING_API AMachinePlug : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	//void Interact() override;

	UPROPERTY(EditInstanceOnly)
	FString Letter;

	UPROPERTY(EditInstanceOnly)
	TWeakObjectPtr<AMachineCable> ConnectedCable = nullptr;

	int32 GetLetterIndex()
	{
		if (Letter.Len() == 0)
			return -1;

		return Letter[0] - 'A';
	}

	bool HasConnectedPlug();
	TWeakObjectPtr<AMachinePlug> GetConnectedPlug();
	void DisconnectPlug();
	void ConnectPlug(TWeakObjectPtr<AMachinePlug> Plug);
};
