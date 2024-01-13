// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/DAction.h"
#include "DAction_GetUp.generated.h"

class ADCharacter;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_GetUp : public UDAction
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Knockback")
	TObjectPtr<UAnimMontage> GetUpAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float GetUpAnimDelay;

	UFUNCTION()
	void GetUpDelay_Elapsed(ACharacter* InstigatorCharacter);

	ADCharacter* Character;
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

	UDAction_GetUp();
};
