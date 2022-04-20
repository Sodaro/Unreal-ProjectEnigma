#pragma once
#include "InteractableObject.h"
#include "BlueprintInteractable.generated.h"

UCLASS()
class ABlueprintInteractable : public AInteractableObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
	void Interact() override;
};