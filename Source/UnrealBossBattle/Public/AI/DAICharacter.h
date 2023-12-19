#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DAICharacter.generated.h"

class UDActionComponent;

UCLASS()
class UNREALBOSSBATTLE_API ADAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAICharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDActionComponent* ActionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
