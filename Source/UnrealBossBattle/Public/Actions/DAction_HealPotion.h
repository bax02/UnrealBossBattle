// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/DAction.h"
#include "DAction_HealPotion.generated.h"

class ACharacter;
class UDCharacterAttributeComponent;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_HealPotion : public UDAction
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Heal")
	TObjectPtr<UAnimMontage> HealAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	float HealAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	float HealAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	FName BoneName;

	UFUNCTION()
	void HealDelay_Elapsed(ACharacter* InstigatorCharacter);

	UFUNCTION()
	void ApplyHealDelay_Elapsed(ACharacter* InstigatorCharacter);

	UPROPERTY()
	ACharacter* Character;

	UPROPERTY()
	UDCharacterAttributeComponent* CharacterAttributeComp;


public:

	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

	UDAction_HealPotion();
	
};
