// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBTService_Random.h"
#include "BehaviorTree/BlackboardComponent.h"

void UDBTService_Random::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComp))
	{
		int RandomNumber = FMath::RandRange(Min, Max);
		BlackboardComp->SetValueAsInt(RandomKey.SelectedKeyName, RandomNumber);
	}
}
