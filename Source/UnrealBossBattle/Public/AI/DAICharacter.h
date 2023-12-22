#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DAICharacter.generated.h"

class UDAttributeComponent;
class UCapsuleComponent;
class UParticleSystemComponent;
class UParticleSystem;


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
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> HitSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
