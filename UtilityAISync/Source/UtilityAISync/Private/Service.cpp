// // Copyright Yousei. All Rights Reserved.


#include "Service.h"

#include "Action.h"
UUtilityService::UUtilityService()
{
	
}

void UUtilityService::Native_OnBecomeRelevant(AAIController* AIController, APawn* OwnerPawn)
{
	OnBecomeRelevant( AIController,OwnerPawn);
}

void UUtilityService::Native_Tick(float DeltaTime, AAIController* Controller, APawn* Pawn)
{
	Tick(DeltaTime,Controller,Pawn);
	
}

void UUtilityService::Native_OnCeaseRelevant(AAIController* AIController, APawn* OwnerPawn)
{
	OnCeaseRelevant( AIController,OwnerPawn);
}

UWorld* UUtilityService::GetWorld() const
{
	//todo: better imp
	if (HasAllFlags(RF_ClassDefaultObject)) return nullptr;
	
	return Cast<UUtilityAction>(GetOuter())->GetWorld();
}


