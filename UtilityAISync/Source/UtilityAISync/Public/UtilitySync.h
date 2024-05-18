// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "InstancedStruct.h"
#include "Action.h"
#include "UtilitySync.generated.h"

class UBlackboard;
class AAIController;
class UUtilityArchetypeConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTILITYAISYNC_API UUtilitySync : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI",meta=(AllowPrivateAccess))
	TObjectPtr<const UUtilityArchetypeConfig> UtilityArchetypeConfig;
	UPROPERTY()
	TObjectPtr<UBlackboard> Blackboard;
	
	UPROPERTY()
	AAIController* OwnerController;
	UPROPERTY()
	APawn* ControllerPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI",meta=(AllowPrivateAccess))
	float Bounciness=1.f;
	
	float LastSwitchTime;
	UPROPERTY()
	UUtilityAction* LastAction;
	
	UPROPERTY()
	UUtilityAction* BestAction;

	UPROPERTY()
	TArray<UUtilityAction*> InstancedUtilityActions;

	FTimerHandle ScoreActionsTimerHandle;
	FGameplayTag Tag;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility AI")
	FRuntimeFloatCurve GetConsiderationCurve(FGameplayTag ConsiderationTag);
	
	UUtilityAction* ComputeBestAction();
	bool CheckHighestScore(UUtilityAction* Current, UUtilityAction* Best) const;
	void SetupAIController();
	UUtilityAction* CreateAction(const TSubclassOf<UUtilityAction>& ActionClass);
	bool CanCreateAction(const TSubclassOf<UUtilityAction>& ActionClass) const;
public:
	UFUNCTION(BlueprintCallable)
	UBlackboard* GetBlackboard() const {return Blackboard;}
	
	const TArray<UUtilityAction*>& GetInstancedActions() const;

	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUtilityAIActionSpawned, UUtilityAction*, Action);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Action Spawned"))
	FUtilityAIActionSpawned OnUtilityAIActionSpawned;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUtilityAIActionChanged, UUtilityAction*, NewAction, UUtilityAction*, OldAction);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Action Changed"))
	FUtilityAIActionChanged OnUtilityAIActionChanged;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUtilityAIActionNotAvailable);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Action Not Available"))
	FUtilityAIActionNotAvailable OnUtilityAIActionNotAvailable;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUtilityAIInitialized);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Initialized"))
	FUtilityAIInitialized OnUtilityAIInitialized;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUtilityAIActionChoosen, UUtilityAction*, Action);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Action Choosen"))
	FUtilityAIActionChoosen OnUtilityAIActionChosen;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUtilityAIBeforeScoreComputation);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Before Score Computation"))
	FUtilityAIBeforeScoreComputation OnUtilityAIBeforeScoreComputation;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUtilityAIActionTicked, UUtilityAction*, Action);
	UPROPERTY(BlueprintAssignable, Category = "Utility AI", meta = (DisplayName = "On UtilityAI Action Ticked"))
	FUtilityAIActionChoosen OnUtilityAIActionTicked;
	
public:
	// Sets default values for this component's properties
	UUtilitySync();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
};
