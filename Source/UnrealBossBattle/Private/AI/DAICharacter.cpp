#include "AI/DAICharacter.h"
#include "DActionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "DAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADAICharacter::ADAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	CapsuleComp->SetupAttachment(GetMesh(), "HammerCenter");
	CapsuleComp->ComponentTags.Add("WeaponCollision");

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(GetMesh(), "Root");
}

// Called when the game starts or when spawned
void ADAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ADAICharacter::OnActorOverlap);
}

void ADAICharacter::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		DrawDebugCapsule(GetWorld(), CapsuleComp->GetComponentLocation(), CapsuleComp->GetScaledCapsuleHalfHeight(),
			CapsuleComp->GetScaledCapsuleRadius(), CapsuleComp->GetComponentRotation().Quaternion(), FColor::Red, false, 2.0f);
		CapsuleComp->SetGenerateOverlapEvents(false);

		UGameplayStatics::SpawnEmitterAttached(HitParticles, GetMesh(), "HammerCenter", FVector::ZeroVector,
			FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true, EPSCPoolMethod::AutoRelease);

		UGameplayStatics::SpawnSoundAttached(HitSound, CapsuleComp);

		UDAttributeComponent* HitAttributeComp = UDAttributeComponent::GetAttributes(OtherActor);

		if (HitAttributeComp)
		{
			HitAttributeComp->ApplyHealthChange(-20.f);
		}
	}
}

// Called every frame
void ADAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}