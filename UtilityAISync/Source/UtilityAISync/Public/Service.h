// // Copyright Yousei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "Service.generated.h"

class AAIController;

UCLASS(Abstract, BlueprintType, Blueprintable)
class UTILITYAISYNC_API UUtilityService : public UObject
{
	GENERATED_BODY()
	
	

	
public:
	virtual UWorld* GetWorld() const override;
	UUtilityService();
	//temp
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DependencyActionTag;

	UFUNCTION(BlueprintImplementableEvent)
	void OnBecomeRelevant(AAIController* AIController, APawn* OwnerPawn);
	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaTime, AAIController* Controller, APawn* Pawn);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCeaseRelevant(AAIController* AIController, APawn* OwnerPawn);
	void Native_OnBecomeRelevant(AAIController* AIController, APawn* OwnerPawn);
	void Native_Tick(float DeltaTime, AAIController* Controller, APawn* Pawn);
	void Native_OnCeaseRelevant(AAIController* AIController, APawn* OwnerPawn);

	
};
