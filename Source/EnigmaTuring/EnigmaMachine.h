#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnigmaMachine.generated.h"


class ARotorWheel;

class AMachineLamp;
class AMachineKey;

class UMachineTextOutput;

UENUM(BlueprintType)
enum RingPosition
{
	LEFT UMETA(DisplayName = "LEFT"),
	MID UMETA(DisplayName = "MID"),
	RIGHT UMETA(DisplayName = "RIGHT")
};

USTRUCT()
struct FKeyLampPair
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	AMachineLamp* Lamp;
	UPROPERTY(EditInstanceOnly)
	AMachineKey* Key;
};

UCLASS()
class ENIGMATURING_API AEnigmaMachine : public AActor
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	TArray<ARotorWheel*> RotorWheels;

	UPROPERTY(EditInstanceOnly)
	ARotorWheel* ReflectorWheel;

	UPROPERTY(EditInstanceOnly)
	TMap<FString, FKeyLampPair> KeyLampPairs;

	FString LastLampKey = "";

	FString OutputText = "";

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<UMachineTextOutput> OutputWidgetClass;

	UMachineTextOutput* OutputWidget;

	void PressKey(int32 AlphabetIndex);
	int32 EncodeLetter(int32 AlphabetIndex);
};

