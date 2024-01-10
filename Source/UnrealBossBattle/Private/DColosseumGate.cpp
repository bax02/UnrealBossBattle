// Fill out your copyright notice in the Description page of Project Settings.


#include "DColosseumGate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DGameModeBase.h"

// Sets default values
ADColosseumGate::ADColosseumGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>("GateMesh");
	RootComponent = GateMesh;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(GateMesh);
}

// Called when the game starts or when spawned
void ADColosseumGate::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADColosseumGate::OnOverlap);
	
}

void ADColosseumGate::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SphereComp->SetGenerateOverlapEvents(false);

	ADGameModeBase* GameMode = Cast<ADGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->StartBattle(OtherActor);
	}
}