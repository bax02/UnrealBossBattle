// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "DCapsuleHitboxComponent.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDCapsuleHitboxComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:

	UDCapsuleHitboxComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage;

	ACharacter* OwningCharacter;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void BeginPlay() override;

};
