// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/DAction.h"
#include "DAction_Knockback.generated.h"

class ADCharacter;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_Knockback : public UDAction
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Knockback")
	TObjectPtr<UAnimMontage> KnockbackAnim;

	UPROPERTY(EditAnywhere, Category = "Knockback")
	TObjectPtr<UAnimMontage> GetUpAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float KnockbackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float ImpulseStrength;

	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	double ZLaunchForce;

	UFUNCTION()
	void KnockbackDelay_Elapsed(ACharacter* InstigatorCharacter);

	ADCharacter* Character;


public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	UDAction_Knockback();
};
