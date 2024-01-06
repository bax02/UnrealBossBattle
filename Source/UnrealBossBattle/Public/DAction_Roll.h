// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "DAction_Roll.generated.h"

class ACharacter;
class UDCharacterAttributeComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = "Roll")
	float StaminaCost;

	UFUNCTION()
	void RollDelay_Elapsed(ACharacter* InstigatorCharacter);

	UPROPERTY(EditAnywhere, Category = "Roll")
	TObjectPtr<USoundBase> RollingSound;

	UPROPERTY()
	ACharacter* Character;

	UPROPERTY()
	UDCharacterAttributeComponent* CharacterAttributeComp;



public:

	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;


	UDAction_Roll();
	
};
