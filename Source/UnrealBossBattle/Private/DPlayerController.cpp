// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"
#include "Blueprint/UserWidget.h"

void ADPlayerController::BeginPlay()
{
	bIsUsingGamepad = false;
}

void ADPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	HealthWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);
	ShowUI();

	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());

}

void ADPlayerController::HideUI()
{
	HealthWidgetInstance->RemoveFromParent();
}

void ADPlayerController::ShowUI()
{
	HealthWidgetInstance->AddToViewport();
}
