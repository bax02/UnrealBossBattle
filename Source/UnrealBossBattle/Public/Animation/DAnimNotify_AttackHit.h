// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DAnimNotify_AttackHit.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotify_AttackHit : public UAnimNotify
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	FName TraceSocket;
		
	UPROPERTY(EditAnywhere, Category = "Animation")
	float SphereRadius;

	UPROPERTY(EditAnywhere, Category = "Animation")
	FVector LocationOffset;

	UPROPERTY(EditAnywhere, Category = "Particles")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> HitSound;

public:
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	bool ShouldFireInEditor() override { return false; }
};
