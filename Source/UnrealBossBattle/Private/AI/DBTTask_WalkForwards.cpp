// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBTTask_WalkForwards.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"

UDBTTask_WalkForwards::UDBTTask_WalkForwards()
{
	SpeedDifference = -0.f;
	bNotifyTick = true;
}

EBTNodeResult::Type UDBTTask_WalkForwards::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		Character = Cast<ACharacter>(Controller->GetPawn());
		if (Character)
		{
			MovementComp = Character->GetComponentByClass<UCharacterMovementComponent>();
			if (ensure(MovementComp))
			{
				MovementComp->MaxWalkSpeed = MovementComp->MaxWalkSpeed + SpeedDifference;
			}			
			FRotator ControlRot = Character->GetControlRotation();
			ControlRot.Pitch = 0.0f;
			ControlRot.Roll = 0.0f;
			ForwardVector = ControlRot.Vector();
		}
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UDBTTask_WalkForwards::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Character->AddMovementInput(ForwardVector, 1.f);
}


EBTNodeResult::Type UDBTTask_WalkForwards::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MovementComp->MaxWalkSpeed = MovementComp->MaxWalkSpeed - SpeedDifference;
	return Super::AbortTask(OwnerComp, NodeMemory);
}
