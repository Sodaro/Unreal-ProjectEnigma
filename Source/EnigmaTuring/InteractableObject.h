// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

//class UMaterialInstanceDynamic;
class UStaticMeshComponent;

UCLASS()
class ENIGMATURING_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	void ChangeColor(FLinearColor color);
};