// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DBTService_Random.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDBTService_Random : public UBTService
{
	GENERATED_BODY()

	protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	int Min;

	UPROPERTY(EditAnywhere, Category = "AI")
	int Max;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector RandomKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
