// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "DAction_Attack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_Attack : public UDAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackAnim;

	bool bContinueCombo;

	int comboCount = 0;

public:

	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
	
};
