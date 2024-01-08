// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "DCharacter.h"
#include "AI/DAICharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "DDoor.h"

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

    if (DoorInstance)
    {
        DoorInstance->OnDoorInteract.AddDynamic(this, &ADGameModeBase::StopAmbience);
    }

    MusicInstance = UGameplayStatics::SpawnSound2D(GetWorld(), MainMenuMusic);
}

void ADGameModeBase::StartGame()
{
    AmbienceInstance = UGameplayStatics::SpawnSound2D(GetWorld(), SandAmbience);

    LevelSequencePlayer->Stop();

    UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

    OnGameStart.Broadcast();

    APlayerController* Controller = GetWorld()->GetFirstPlayerController();
    RestartPlayer(Controller);
}

void ADGameModeBase::StartBattle(AActor* PlayerActor)
{
    // Stop menu music and play battle music
    MusicInstance->Stop();
    MusicInstance = UGameplayStatics::SpawnSound2D(GetWorld(), BattleMusic);

    // Play Battle Sequence (Cutscene)
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

void ADGameModeBase::OnActorKilled(AActor* VictimActor, AActor* InstigatorActor)
{
    //Stop battle music
    MusicInstance->FadeOut(2.0f, 0.0f);

    float DeathDelay = 3.0f;
    // Player Death
    ADCharacter* Player = Cast<ADCharacter>(VictimActor);
    if (Player)
    {
        // Play Death Anim and Disable Input
        Player->PlayDeathAnim();

        // Unpossess the AI Character
        ADAICharacter* InstigatorCharacter = Cast<ADAICharacter>(InstigatorActor);
        InstigatorCharacter->GetController()->UnPossess();

        // Show Death Widget
        WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), DeathWidgetClass);
        WidgetInstance->AddToViewport();
    }
    else
    {
        ADAICharacter* AICharacter = Cast<ADAICharacter>(VictimActor);
        // AI Death
        if (AICharacter)
        {
            // Play AI Death Anim
            AICharacter->PlayDeathAnim();

            // Unpossess the AI Character
            AICharacter->GetController()->UnPossess();

            // Show Victory Widget
            WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), VictoryWidgetClass);
            WidgetInstance->AddToViewport();

            DeathDelay = 7.0f;
        }
    }



    FTimerHandle TimerHandle_DeathDelay;
    FTimerDelegate Delegate;
    Delegate.BindUFunction(this, "DeathDelay_Elapsed");

    GetWorld()->GetTimerManager().SetTimer(TimerHandle_DeathDelay, Delegate, DeathDelay, false);
}

void ADGameModeBase::DeathDelay_Elapsed()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void ADGameModeBase::StopAmbience()
{
    UE_LOG(LogTemp, Log, TEXT("Try STOP Ambience"));
    if (AmbienceInstance)
    {
        UE_LOG(LogTemp, Log, TEXT("Stopping Ambience"));
        AmbienceInstance->Stop();
    }
}
