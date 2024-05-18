// Fill out your copyright notice in the Description page of Project Settings.

#include "Action.h"
#include "UtilitySync.h"
#include "AIController.h"
#include "Service.h"


bool UUtilityAction::ReceiveCanRun_Implementation(AAIController* AIController, APawn* OwnerPawn) const
{
	return  !IsActive() || !EvaluateScore()==0;
}
void UUtilityAction::Native_ReceiveStart(AAIController* AIController, APawn* OwnerPawn)
{
	//Instantiate and init service
	for (const auto& Service : UtilityServices)
	{
		auto* NewService=NewObject<UUtilityService>(this,Service);
		NewService->Native_OnBecomeRelevant( AIController,OwnerPawn);
		Services.Emplace(NewService);
	}
	
	bIsActive=true;
	ReceiveStart( AIController,OwnerPawn);
	
}

void UUtilityAction::Native_ReceiveTick(float DeltaTime, AAIController* Controller, APawn* Pawn)
{
	for (const auto& Service : Services)
	{
		if (Service->IsValidLowLevel())
		{
			Service->Native_Tick(DeltaTime,Controller,Pawn);
		}
	}
	ReceiveTick(DeltaTime,Controller,Pawn);
	
}


void UUtilityAction::Native_ReceiveEnd(AAIController* AIController, APawn* OwnerPawn)
{
	//Destroy Services
	for (const auto& Service : Services)
	{
		if (Service->IsValidLowLevel())
		{
			Service->Native_OnCeaseRelevant(AIController,OwnerPawn);
			Service->MarkAsGarbage();



			
		}
	}
	bIsActive=false;
	ReceiveEnd(AIController, OwnerPawn);
	
}
TArray<UCurveFloat*> UUtilityAction::GetConsiderationCurves() const
{
	TArray<UCurveFloat*> Curves;

	for (const auto& Curve : Considerations)
	{
		Curves.Emplace( Curve.Value);
	}
	return  Curves;
}

UWorld* UUtilityAction::GetWorld() const
{
	if (HasAllFlags(RF_ClassDefaultObject)) return nullptr;
	
	return UtilitySync->GetWorld();
}

void UUtilityAction::SetOwner()
{
	UtilitySync=Cast<UUtilitySync>(GetOuter());
	OwnerController=Cast<AAIController>(UtilitySync->GetOwner());
}

