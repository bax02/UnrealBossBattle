// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "DAction_Block.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAction_Block : public UDAction
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Block")
	TObjectPtr<UAnimMontage> BlockAnim;

	UPROPERTY(EditAnywhere, Category = "Block")
	TObjectPtr<USoundBase> BlockingSound;

	UPROPERTY()
	ACharacter* Character;

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

	static bool BlockHit(ACharacter* HitCharacter, UParticleSystem* HitParticles, USoundBase* HitSound);

	
};
