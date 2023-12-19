// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DBTTask_PerformAction.generated.h"

class UDAction;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDBTTask_PerformAction : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> AnimMontage;

	UFUNCTION()
	void AnimMontageDelay_Elapsed(UBehaviorTreeComponent* OwnerComp);

	UPROPERTY(EditAnywhere, Category = "Animation")
	float TransitionTime;

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
