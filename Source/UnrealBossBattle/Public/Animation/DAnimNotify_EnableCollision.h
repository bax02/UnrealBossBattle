// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DAnimNotify_EnableCollision.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotify_EnableCollision : public UAnimNotify
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Animation")
	bool bDisableCollision;

	UPROPERTY(EditAnywhere, Category = "Animation")
	bool bChangeHitbox;
		
	UPROPERTY(EditAnywhere, Category = "Animation")
	float ExtendHitboxHalfHeight;


public:
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	#if WITH_EDITORONLY_DATA
	bool ShouldFireInEditor() override { return false; };
	#endif
};
