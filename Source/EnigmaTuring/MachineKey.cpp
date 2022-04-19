// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineKey.h"
#include "EnigmaMachine.h"
void AMachineKey::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
	EndPosition = StartPosition - FVector(0, 0, 9);
}
void AMachineKey::Interact()
{
	PlayPressAnimation(0.25f);
	EnigmaMachine->EncodeLetter(Letter[0] - 'A');
}

AMachineKey::AMachineKey()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
}

void AMachineKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PressTimer += DeltaTime;
	if (PressTimer > PressDuration)
		PressTimer = PressDuration;

	FVector NewPosition;
	if (IsPressed)
	{
		NewPosition = FMath::Lerp(StartPosition, EndPosition, PressTimer / PressDuration);
	}
	else
	{
		NewPosition = FMath::Lerp(EndPosition, StartPosition, PressTimer / PressDuration);
	}

	SetActorLocation(NewPosition);

	if (PressTimer == PressDuration)
	{
		if (IsPressed)
		{
			IsPressed = false;
			PressTimer = 0;
		}
		else
		{
			PrimaryActorTick.SetTickFunctionEnable(false);
			PressTimer = 0;
		}
	}
}

void AMachineKey::PlayPressAnimation(float Duration)
{
	PrimaryActorTick.SetTickFunctionEnable(true);
	IsPressed = true;
	PressDuration = Duration;
}
