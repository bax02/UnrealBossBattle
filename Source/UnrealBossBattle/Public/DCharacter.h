// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputAction.h"
#include "DCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UDActionComponent;
class UDAttributeComponent;

UCLASS()
class UNREALBOSSBATTLE_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	// Actions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDActionComponent* ActionComp;

	// Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDAttributeComponent* AttributeComp;

	// Enhanced Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_LookMouse;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_LookStick;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Sprint;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Roll;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Attack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Block;

	void Move(const FInputActionInstance& Instance);

	void LookMouse(const FInputActionValue& InputValue);

	void LookStick(const FInputActionValue& InputValue);

	void SprintStart();

	void SprintStop();

	void RollStart();

	void AttackStart();

	void BlockStart();

	void BlockStop();

public:
	// Sets default values for this character's properties
	ADCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
