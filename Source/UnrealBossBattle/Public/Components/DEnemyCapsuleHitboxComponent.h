// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DCapsuleHitboxComponent.h"
#include "DEnemyCapsuleHitboxComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDEnemyCapsuleHitboxComponent : public UDCapsuleHitboxComponent
{
	GENERATED_BODY()

protected:
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
