// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "DAction_BossCombo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_BossCombo : public UDAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Roll")
	TObjectPtr<UAnimMontage> ComboAnim;

	UFUNCTION()
	void ComboDelay_Elapsed(ACharacter* InstigatorCharacter);

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;
	
};
