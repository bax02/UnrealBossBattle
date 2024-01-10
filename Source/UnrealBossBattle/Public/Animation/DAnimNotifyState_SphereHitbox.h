// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DAnimNotifyState_SphereHitbox.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotifyState_SphereHitbox : public UAnimNotifyState
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

	FTimerHandle TimerHandle_UpdateHitbox;

	UFUNCTION()
	void UpdateHitbox();

	ACharacter* Character;

	FVector TracePoint;

	FCollisionShape Shape;

	FCollisionObjectQueryParams ObjParams;

	FCollisionQueryParams Params;
	
public:

	#if WITH_EDITORONLY_DATA
	bool ShouldFireInEditor() override { return false; };
	#endif

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
