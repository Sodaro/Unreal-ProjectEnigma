// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "MachinePlug.generated.h"

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
	TWeakObjectPtr<AMachinePlug> ConnectedPlug = nullptr;

	int32 GetLetterIndex()
	{
		if (Letter.Len() == 0)
			return -1;

		return Letter[0] - 'A';
	}

	bool HasConnectedPlug() { return ConnectedPlug != nullptr; }
	TWeakObjectPtr<AMachinePlug> GetConnectedPlug() { return ConnectedPlug; }
	void DisconnectPlug();
	void ConnectPlug(TWeakObjectPtr<AMachinePlug> Plug);
};
