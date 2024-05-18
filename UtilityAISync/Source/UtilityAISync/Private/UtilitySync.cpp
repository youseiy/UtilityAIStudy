// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilitySync.h"

#include "Action.h"
#include "Blackboard.h"
#include "Misc/UtilityAchtypeConfig.h"
#include "Runtime/AIModule/Classes/AIController.h"


// Sets default values for this component's properties
UUtilitySync::UUtilitySync()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	Blackboard=NewObject<UBlackboard>(this,UBlackboard::StaticClass(),FName("UtilityBlackboard"));
	
}



// Called when the game starts
void UUtilitySync::BeginPlay()
{
	Super::BeginPlay();
	SetupAIController();
	OnUtilityAIInitialized.Broadcast();
	
	LastAction = nullptr;
	LastSwitchTime = 0;

	// instantiate actions
	for (const auto& Action : UtilityArchetypeConfig->UtilityActions)
	{
		CreateAction( Action.Value.LoadSynchronous());
	}

	OnUtilityAIInitialized.Broadcast();

	
}


// Called every frame
void UUtilitySync::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//todo: move to timer 
	
	// Check if OwnerController is valid
	if (!OwnerController)
		return;

	// Broadcast an event before computing scores
	OnUtilityAIBeforeScoreComputation.Broadcast();

	// Compute the best action based on utility scores
	BestAction = ComputeBestAction();

	
	// Check if a best action is available
	if (BestAction)
	{
		// Broadcast an event with the chosen action
		OnUtilityAIActionChosen.Broadcast(BestAction);

		// Check if the chosen action is different from the last action
		if (LastAction != BestAction)
		{
			float CurrentTime = GetWorld()->GetTimeSeconds();
			// Avoid too fast action switching
			if (LastSwitchTime == 0 || CurrentTime - LastSwitchTime > Bounciness)
			{
				// Broadcast an event with the changed action
				OnUtilityAIActionChanged.Broadcast(BestAction, LastAction);
				// End the last action and start the new action
				if (LastAction)
				{
					LastAction->Native_ReceiveEnd(OwnerController, OwnerController->GetPawn());
				}
				BestAction->Native_ReceiveStart(OwnerController, OwnerController->GetPawn());
				LastSwitchTime = CurrentTime;
			}
			else
			{
				// Fast exit if nothing to run
				if (!LastAction)
					return;
				// Use the last action if not enough time has passed
				BestAction = LastAction;
			}
		}
	}
	// Tick the best action
	BestAction->Native_ReceiveTick(DeltaTime, OwnerController, OwnerController->GetPawn());
	// Update the last action
	LastAction = BestAction;
	// Broadcast an event for the ticked action
	OnUtilityAIActionTicked.Broadcast(BestAction);
}

void UUtilitySync::SetupAIController()
{
	OwnerController=Cast<AAIController>(GetOwner());
	ControllerPawn=OwnerController->GetPawn();
	
}

UUtilityAction* UUtilitySync::CreateAction(const TSubclassOf<UUtilityAction>& ActionClass)
{
	// skip null
	if (!ActionClass)
		return nullptr;

	// avoid duplicates
	if (!CanCreateAction(ActionClass))
		return nullptr;

	AAIController* Controller = Cast<AAIController>(GetOwner());
	if (!Controller)
		return nullptr;

	
	UUtilityAction* Action=NewObject<UUtilityAction>(this,ActionClass);



	
	Action->SetOwner();
	InstancedUtilityActions.Emplace( Action);
	OnUtilityAIActionSpawned.Broadcast(Action);
	return Action;
}

bool UUtilitySync::CanCreateAction(const TSubclassOf<UUtilityAction>& ActionClass) const
{
	for (const auto& Action : InstancedUtilityActions)
	{
		if (Action->GetClass() == ActionClass)
			return false;
	}
	return true;
}

FRuntimeFloatCurve UUtilitySync::GetConsiderationCurve(FGameplayTag ConsiderationTag) 
{
	for (const auto& Element : UtilityArchetypeConfig->UtilityConsiderations)
	{
		if (Element.Key==ConsiderationTag)
		{
			return Element.Value;
		}
	}
	return {};
}

UUtilityAction* UUtilitySync::ComputeBestAction()
{
	float BestScore = -FLT_MAX;

	for (const auto& ActionPair : InstancedUtilityActions)
	{
		
		UUtilityAction* Action = ActionPair;

		// Check if the action can run
		if (!Action->ReceiveCanRun(OwnerController, ControllerPawn))
			continue;

		// Calculate the score for the action
		float ActionScore = Action->EvaluateScore();
		
		// Update the best action if this action has a higher score
		if (ActionScore > BestScore)
		{
			BestAction = Action;
			BestScore = ActionScore;
		}
	}
	return BestAction;
}

bool UUtilitySync::CheckHighestScore(UUtilityAction* Current, UUtilityAction* Best) const
{
	// Fast case: if Best is nullptr, Current is considered to have the highest score
	if (!Best)
		return true;

	// If the absolute difference between the last scores is non-zero, return false
	if (FMath::Abs(Best->LastScore - Current->LastScore) > SMALL_NUMBER)
	{
		
		return false;
		
	}

	// If Current has a higher score than Best, return true
	if (Current->LastScore > Best->LastScore)
	{
		return true;
	}

	// Otherwise, return false
	return false;
}

const TArray<UUtilityAction*>& UUtilitySync::GetInstancedActions() const
{
	return InstancedUtilityActions;
}

