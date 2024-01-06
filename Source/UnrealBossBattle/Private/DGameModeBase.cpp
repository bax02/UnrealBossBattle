// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

ADGameModeBase::ADGameModeBase()
{
    bStartPlayersAsSpectators = true;
}

void ADGameModeBase::StartPlay()
{
	Super::StartPlay();

    ALevelSequenceActor* OutActor;
    FMovieSceneSequencePlaybackSettings PlaybackSettings;
    PlaybackSettings.LoopCount.Value = -1;

    LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MainMenuSequence, PlaybackSettings, OutActor);

    if (LevelSequencePlayer)
    {
        LevelSequencePlayer->Play();
    }
}

void ADGameModeBase::StartGame()
{
    LevelSequencePlayer->Stop();

    UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

    OnGameStart.Broadcast();

    APlayerController* Controller = GetWorld()->GetFirstPlayerController();
    RestartPlayer(Controller);
}

void ADGameModeBase::StartBattle(AActor* PlayerActor)
{
    ALevelSequenceActor* OutActor;
    LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), BeginBattleSequence, FMovieSceneSequencePlaybackSettings(), OutActor);
    
    TArray<AActor*> ActorArray;
    ActorArray.Add(PlayerActor);

    OutActor->SetBindingByTag("Player", ActorArray);
    if (LevelSequencePlayer)
    {
        LevelSequencePlayer->Play();
    }
}

