// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAttributeComponent.h"
#include "DCharacterAttributeComponent.generated.h"

class ADCharacter;
class UDActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStaminaChanged, AActor*, InstigatorActor, UDCharacterAttributeComponent*, OwningComp, float, NewStamina, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPotionChanged, UDCharacterAttributeComponent*, OwningComp, int, NewPotions);


/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class UNREALBOSSBATTLE_API UDCharacterAttributeComponent : public UDAttributeComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxStamina;

	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	int MaxPotions;

	int Potions;

	FTimerHandle TimerHandle_UpdateStamina;

	FTimerHandle TimerHandle_StaminaCooldown;

	ADCharacter* OwningCharacter;

	UDActionComponent* OwningActionComp;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyStaminaChange(float Delta, float Cooldown);

	UFUNCTION()
	void UpdateStamina();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyPotionChange(int Delta);

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPotionChanged OnPotionChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UDCharacterAttributeComponent* GetCharacterAttributes(AActor* FromActor);

	void BeginPlay() override;

	UDCharacterAttributeComponent();
		
	
};
