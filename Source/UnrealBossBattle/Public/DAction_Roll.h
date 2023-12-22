// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "DAction_Roll.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_Roll : public UDAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Roll")
	TObjectPtr<UAnimMontage> RollAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Roll")
	float RollAnimDelay;

	UFUNCTION()
	void RollDelay_Elapsed(ACharacter* InstigatorCharacter);

	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<USoundBase> RollingSound;


public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	UDAction_Roll();
	
};
