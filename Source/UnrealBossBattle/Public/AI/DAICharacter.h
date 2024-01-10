#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DAICharacter.generated.h"

class UDAttributeComponent;
class UParticleSystemComponent;
class UDCapsuleHitboxComponent;


UCLASS()
class UNREALBOSSBATTLE_API ADAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAICharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDCapsuleHitboxComponent* HitboxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	// Animations
	UPROPERTY(EditAnywhere, Category = "Death")
	TObjectPtr<UAnimMontage> DeathAnim;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void PlayDeathAnim();

};
