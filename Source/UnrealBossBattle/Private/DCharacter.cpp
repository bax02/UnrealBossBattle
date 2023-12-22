// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DActionComponent.h"
#include "DAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Enhanced Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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

	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	CapsuleComp->SetupAttachment(GetMesh(), "SwordCenter");
	CapsuleComp->ComponentTags.Add("WeaponCollision");

}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADCharacter::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		DrawDebugCapsule(GetWorld(), CapsuleComp->GetComponentLocation(), CapsuleComp->GetScaledCapsuleHalfHeight(),
			CapsuleComp->GetScaledCapsuleRadius(), CapsuleComp->GetComponentRotation().Quaternion(), FColor::Blue, false, 2.0f);
		CapsuleComp->SetGenerateOverlapEvents(false);

		UDAttributeComponent* HitAttributeComp = UDAttributeComponent::GetAttributes(OtherActor);

		UGameplayStatics::SpawnSoundAttached(HitSound, CapsuleComp);

		if (HitAttributeComp)
		{
			HitAttributeComp->ApplyHealthChange(-20.f);
		}

	}
}

void ADCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ADCharacter::OnActorOverlap);
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

void ADCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ADCharacter::SprintStop()
{
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

