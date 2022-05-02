#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

class UStaticMeshComponent;

DECLARE_DELEGATE_OneParam(InteractDelegate, AInteractableObject*)

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
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	InteractDelegate OnInteract;

	virtual void Interact();
	virtual void Hover();
};
