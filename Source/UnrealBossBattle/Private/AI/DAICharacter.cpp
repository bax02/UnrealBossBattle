#include "AI/DAICharacter.h"
#include "DActionComponent.h"
//#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "DAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DCapsuleHitboxComponent.h"

// Sets default values
ADAICharacter::ADAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(GetMesh(), "pelvis");

	HitboxComp = CreateDefaultSubobject<UDCapsuleHitboxComponent>("HitboxComp");
	HitboxComp->SetupAttachment(GetMesh(), "HammerCenter");
	HitboxComp->ComponentTags.Add("WeaponCollision");
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