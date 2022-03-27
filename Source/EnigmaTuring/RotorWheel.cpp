// Fill out your copyright notice in the Description page of Project Settings.


#include "RotorWheel.h"
#include <Components/TextRenderComponent.h>
ARotorWheel::ARotorWheel()
{

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	Text->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARotorWheel::BeginPlay()
{
	Super::BeginPlay();
	Text->Text = FText::FromString(DisplayedText);
}

void ARotorWheel::Interact()
{
	Super::Interact();
	++CurrentLetterIndex %= 26;
	if (CurrentLetterIndex == 0 && NextWheel != nullptr)
		NextWheel->Interact();

	float amount = 360.f / 26;
	DisplayedText = "";
	DisplayedText = DisplayedText.AppendChar(LetterArr[CurrentLetterIndex]);
	FQuat rotation = FQuat::MakeFromEuler(FVector{ 0, amount, 0 });
	Mesh->AddRelativeRotation(rotation);
	Text->SetText(FText::FromString(DisplayedText));
}
