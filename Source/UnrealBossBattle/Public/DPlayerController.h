// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	void OnPossess(APawn* aPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthWidgetClass;

	UPROPERTY()
	UUserWidget* HealthWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bIsUsingGamepad;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideUI();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowUI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
