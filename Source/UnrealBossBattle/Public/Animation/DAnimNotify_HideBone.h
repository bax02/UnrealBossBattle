// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DAnimNotify_HideBone.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotify_HideBone : public UAnimNotify
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Animation")
	bool bShowBone;

	UPROPERTY(EditAnywhere, Category = "Animation")
	FName BoneName;


public:
	
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
