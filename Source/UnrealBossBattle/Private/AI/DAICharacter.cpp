#include "AI/DAICharacter.h"
#include "DActionComponent.h"
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
	PrimaryActorTick.bCanEverTick = false;

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

void ADAICharacter::PlayDeathAnim()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);
	PlayAnimMontage(DeathAnim);
}
