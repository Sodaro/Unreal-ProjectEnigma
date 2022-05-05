// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "MachineCablePlug.generated.h"

class AMachinePort;
class AMachineCable;
class UBoxComponent;

UCLASS()
class ENIGMATURING_API AMachineCablePlug : public AInteractableObject
{
	GENERATED_BODY()


public:

	AMachineCablePlug();

	UPROPERTY(BlueprintReadWrite)
	FVector BoxExtents;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere)
	AMachinePort* OverlappedPort;
	
	UPROPERTY()
	TWeakObjectPtr<AMachineCable> Cable;

	//UFUNCTION()
	//TWeakObjectPtr<AMachinePort> GetSwappedPort() const;
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);
	
	UFUNCTION()
	void HandleEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//void Interact() override;
};
