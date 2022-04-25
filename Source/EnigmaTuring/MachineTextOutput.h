#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MachineTextOutput.generated.h"

UCLASS()
class UMachineTextOutput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetText(const FString& Text);
};
