// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DBTTask_WalkForwards.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDBTTask_WalkForwards : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SpeedDifference;

	ACharacter* Character;

	UCharacterMovementComponent* MovementComp;

	FVector ForwardVector;

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UDBTTask_WalkForwards();

	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
