// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DAnimNotify_AttackHit.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotify_AttackHit : public UAnimNotify
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = "Animation")
	FName TraceStartSocket;

	UPROPERTY(EditAnywhere, Category = "Animation")
	FName TraceEndSocket;
		
	UPROPERTY(EditAnywhere, Category = "Animation")
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float CapsuleHalfHeight;

public:
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	bool ShouldFireInEditor() override { return false; }
};
