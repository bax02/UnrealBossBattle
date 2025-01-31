// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/DAction.h"
#include "DAction_Sprint.generated.h"

class UDCharacterAttributeComponent;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_Sprint : public UDAction
{
	GENERATED_BODY()

protected:

	// Bonus speed to add to Character
	UPROPERTY(EditAnywhere, Category="Targeting")
	float BonusSpeed = 200;

	UDCharacterAttributeComponent* CharacterAttributeComp;


public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;


	
};
