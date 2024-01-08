// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;
class ADDoor;

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

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> DeathWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> VictoryWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Music")
	TObjectPtr<USoundBase> MainMenuMusic;

	UPROPERTY(EditAnywhere, Category = "Music")
	TObjectPtr<USoundBase> BattleMusic;

	UPROPERTY(EditAnywhere, Category = "Music")
	TObjectPtr<USoundBase> SandAmbience;

	UPROPERTY()
	UAudioComponent* AmbienceInstance;

	UPROPERTY()
	UAudioComponent* MusicInstance;

	UPROPERTY()
	UUserWidget* WidgetInstance;

	UFUNCTION()
	void DeathDelay_Elapsed();

	UPROPERTY(EditAnywhere, Category = "DespawnInteractable")
	TSoftObjectPtr<ADDoor> DoorInstance;

	UFUNCTION()
	void StopAmbience();

public:

	virtual void StartPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnGameStart OnGameStart;

	
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartGame();
	
	void StartBattle(AActor* PlayerActor);

	void OnActorKilled(AActor* VictimActor, AActor* InstigatorActor);

	ADGameModeBase();

};
