// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Engine/EngineTypes.h"
#include "DBTService_CheckAttackRange.generated.h"


/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	float Distance;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	UDBTService_CheckAttackRange();
};
