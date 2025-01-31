// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "DActionComponent.generated.h"

class UDAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALBOSSBATTLE_API UDActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(TSubclassOf<UDAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	UDAction* GetAction(TSubclassOf<UDAction> ActionClass) const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsActionOfClassRunning(TSubclassOf<UDAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UDActionComponent* GetActions(AActor* FromActor);

	bool bSprintInputBuffer;
	
	
	UDActionComponent();
	

protected:

	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<UDAction>> DefaultActions;

	UPROPERTY()
	TArray<UDAction*> Actions;

	virtual void BeginPlay() override;
		
};
