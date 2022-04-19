// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MachineLamp.generated.h"

UCLASS()
class ENIGMATURING_API AMachineLamp : public AActor
{
	GENERATED_BODY()
	
public:	

	AMachineLamp();

	void TurnOn();
	void TurnOff();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class UMaterial* OnMaterial;

	UPROPERTY(EditDefaultsOnly)
	class UMaterial* OffMaterial;

protected:
	virtual void BeginPlay() override;
};
