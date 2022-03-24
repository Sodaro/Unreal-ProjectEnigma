// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include <Materials/MaterialInstanceDynamic.h>
#include <Components/StaticMeshComponent.h>
#include <Logging/LogMacros.h>

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
	if (Mesh->GetStaticMesh() != nullptr)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
		Mesh->SetMaterial(0, MaterialInstance);
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, TEXT("Material:" + Mesh->GetMaterial(0)->GetName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MESH WAS NULL"));
	}		
}

void AInteractableObject::ChangeColor(FLinearColor color)
{
	if (MaterialInstance->IsValidLowLevel())
	{
		if (Mesh->GetMaterial(0) != MaterialInstance)
			Mesh->SetMaterial(0, MaterialInstance);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Material:" + Mesh->GetMaterial(0)->GetName()));
		MaterialInstance->SetVectorParameterValue(TEXT("Color"), color);
	}
	
}

