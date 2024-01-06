// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"

void ADAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}

void ADAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BossWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), BossWidgetClass);
	BossWidgetInstance->AddToViewport();
}
