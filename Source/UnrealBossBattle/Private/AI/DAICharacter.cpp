#include "AI/DAICharacter.h"

// Sets default values
ADAICharacter::ADAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

