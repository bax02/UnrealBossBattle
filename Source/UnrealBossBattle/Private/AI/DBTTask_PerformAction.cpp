// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBTTask_PerformAction.h"
#include "GameFramework/Character.h"
#include "AIController.h"

UDBTTask_PerformAction::UDBTTask_PerformAction()
{
	AnimRateScale = 1.0f;
}


EBTNodeResult::Type UDBTTask_PerformAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		Character = Cast<ACharacter>(Controller->GetPawn());
		if (Character)
		{
			AnimMontage->RateScale = AnimRateScale;
			Character->PlayAnimMontage(AnimMontage);
			FTimerHandle TimerHandle_AnimMontageDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "AnimMontageDelay_Elapsed", &OwnerComp);

			const float FinishDelay = (AnimMontage->GetPlayLength() / AnimMontage->RateScale) - TransitionTime;
			UE_LOG(LogTemp, Log, TEXT("Play Length: %f"), AnimMontage->GetPlayLength());
			UE_LOG(LogTemp, Log, TEXT("Rate Scale: %f"), AnimMontage->RateScale);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AnimMontageDelay, Delegate, FinishDelay, false);
		}
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UDBTTask_PerformAction::AnimMontageDelay_Elapsed(UBehaviorTreeComponent* OwnerComp)
{
	FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}

