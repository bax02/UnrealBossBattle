// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBTTask_PerformJump.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UDBTTask_PerformJump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	Character->Jump();

	FTimerHandle TimerHandle_JumpDelay;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "JumpDelay_Elapsed");

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_JumpDelay, Delegate, JumpTime, false);

	return result;
}

void UDBTTask_PerformJump::JumpDelay_Elapsed()
{
	Character->StopJumping();
}