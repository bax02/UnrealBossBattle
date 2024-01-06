// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;
class APawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API ADGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Sequence")
	ULevelSequence* MainMenuSequence;

	UPROPERTY(EditAnywhere, Category = "Sequence")
	ULevelSequence* BeginBattleSequence;

	ULevelSequencePlayer* LevelSequencePlayer;

public:

	virtual void StartPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnGameStart OnGameStart;

	
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartGame();
	
	void StartBattle(AActor* PlayerActor);

	ADGameModeBase();

};
