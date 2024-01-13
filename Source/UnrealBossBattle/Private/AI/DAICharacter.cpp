#include "AI/DAICharacter.h"
#include "Actions/DActionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Attributes/DAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/DEnemyCapsuleHitboxComponent.h"

// Sets default values
ADAICharacter::ADAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(GetMesh(), "pelvis");

	HitboxComp = CreateDefaultSubobject<UDEnemyCapsuleHitboxComponent>("HitboxComp");
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
	ParticleComp->SetVisibility(false);
	GetMesh()->SetGenerateOverlapEvents(false);
	PlayAnimMontage(DeathAnim);
}
