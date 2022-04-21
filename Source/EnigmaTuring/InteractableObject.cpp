// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableObject::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("%s: interaction"), *this->GetName()));
}

void AInteractableObject::Hover()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, TEXT("Logging is enabled!"));

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, FString::Printf(TEXT("%s: hovered"), *this->GetName()));
}
