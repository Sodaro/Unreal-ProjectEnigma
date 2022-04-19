// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineLamp.h"
#include "Components/MeshComponent.h"

// Sets default values
AMachineLamp::AMachineLamp()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(RootComponent);
}

void AMachineLamp::TurnOn()
{
	Mesh->SetMaterial(0, OnMaterial);
}

void AMachineLamp::TurnOff()
{
	Mesh->SetMaterial(0, OffMaterial);
}

void AMachineLamp::BeginPlay()
{
	Super::BeginPlay();
}

