// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DBTTask_PerformAction.h"
#include "DBTTask_PerformJump.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDBTTask_PerformJump : public UDBTTask_PerformAction
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Animation")
	float JumpTime;

	UFUNCTION()
	void JumpDelay_Elapsed();

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
