// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "DActionComponent.h"
#include "DInteractionComponent.h"
#include "DCharacterAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Enhanced Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DCapsuleHitboxComponent.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetUsingAbsoluteRotation(true);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");

	CharacterAttributeComp = CreateDefaultSubobject<UDCharacterAttributeComponent>("AttributeComp");

	InteractionComp = CreateDefaultSubobject<UDInteractionComponent>("InteractionComp");

	HitboxComp = CreateDefaultSubobject<UDCapsuleHitboxComponent>("HitboxComp");
	HitboxComp->SetupAttachment(GetMesh(), "SwordCenter");
	HitboxComp->ComponentTags.Add("WeaponCollision");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bCanMove = true;
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	// Add our mapping context
	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind Actions
	InputComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ADCharacter::Move);
	InputComp->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ADCharacter::Interact);
	InputComp->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ADCharacter::LookMouse);
	InputComp->BindAction(Input_LookStick, ETriggerEvent::Triggered, this, &ADCharacter::LookStick);
	InputComp->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ADCharacter::SprintStart);
	InputComp->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ADCharacter::SprintStop);
	InputComp->BindAction(Input_Roll, ETriggerEvent::Triggered, this, &ADCharacter::RollStart);
	InputComp->BindAction(Input_Attack, ETriggerEvent::Triggered, this, &ADCharacter::AttackStart);
	InputComp->BindAction(Input_Block, ETriggerEvent::Started, this, &ADCharacter::BlockStart);
	InputComp->BindAction(Input_Block, ETriggerEvent::Completed, this, &ADCharacter::BlockStop);
}

void ADCharacter::Move(const FInputActionInstance& Instance)
{
	if (bCanMove)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;

		// Get movement vector from input
		const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
		// Forward/Back
		AddMovementInput(ControlRot.Vector(), AxisValue.Y);

		// Right/Left
		const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, AxisValue.X);
	}
}

void ADCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ADCharacter::LookStick(const FInputActionValue& InputValue)
{
	FVector2D Value = InputValue.Get<FVector2D>();

	// Track negative as we'll lose this during the conversion
	bool XNegative = Value.X < 0.f;
	bool YNegative = Value.Y < 0.f;

	// Can further modify with 'sensitivity' settings
	static const float LookYawRate = 100.0f;
	static const float LookPitchRate = 50.0f;

	// non-linear to make aiming a little easier
	Value = Value * Value;

	if (XNegative)
	{
		Value.X *= -1.f;
	}
	if (YNegative)
	{
		Value.Y *= -1.f;
	}

	AddControllerYawInput(Value.X * LookYawRate * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(Value.Y * LookPitchRate * GetWorld()->GetDeltaSeconds());
}

void ADCharacter::Interact()
{
	InteractionComp->PrimaryInteract();
}

void ADCharacter::SprintStart()
{
	ActionComp->bSprintInputBuffer = true;
	ActionComp->StartActionByName(this, "Sprint");
}

void ADCharacter::SprintStop()
{
	ActionComp->bSprintInputBuffer = false;
	ActionComp->StopActionByName(this, "Sprint");
}

void ADCharacter::RollStart()
{
	ActionComp->StartActionByName(this, "Roll");
}

void ADCharacter::AttackStart()
{
	ActionComp->StartActionByName(this, "Attack");
}

void ADCharacter::BlockStart()
{
	ActionComp->StartActionByName(this, "Block");
}

void ADCharacter::BlockStop()
{
	ActionComp->StopActionByName(this, "Block");
}

void ADCharacter::KnockbackStart(AActor* InstigatorActor)
{
	ActionComp->StartActionByName(InstigatorActor, "Knockback");
}

