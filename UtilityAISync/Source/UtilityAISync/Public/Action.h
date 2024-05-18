// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"

#if !UE_BUILD_SHIPPING
#include <vector>
#endif

#include "Action.generated.h"

class UUtilityService;
class UUtilitySync;
class AAIController;
class UGameplayAbility;


UCLASS(Abstract, BlueprintType, Blueprintable)
class UTILITYAISYNC_API UUtilityAction : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UUtilitySync* UtilitySync;
	UPROPERTY()
	AAIController* OwnerController;
	UPROPERTY()
	TArray<UUtilityService*> Services;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TMap<FGameplayTag,UCurveFloat*> Considerations;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TArray<TSubclassOf< UUtilityService>> UtilityServices;

	bool bIsActive=false;
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	bool bTickEnabled=true;
	
	UFUNCTION(BlueprintCallable,Category="UtilityAI | Action")
	TArray<UCurveFloat*> GetConsiderationCurves() const;
	UFUNCTION(BlueprintCallable,Category="UtilityAI | Action")
	UUtilitySync* GetUtilityComponent() const { return UtilitySync;}
	UFUNCTION(BlueprintCallable,Category="UtilityAI | Action")
	AAIController* GetAIController() const{return OwnerController; }



public:
	virtual UWorld* GetWorld() const override;
	
	void SetOwner();
	
	float LastScore;
	
	bool IsActive() const{return bIsActive;}

	bool TickEnabled() const{return bTickEnabled;}
	
	UFUNCTION(BlueprintNativeEvent)
	bool ReceiveCanRun(AAIController*  AIController, APawn* OwnerPawn) const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStart(AAIController* AIController, APawn* OwnerPawn);
	void Native_ReceiveStart(AAIController* AIController, APawn* OwnerPawn);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveTick(float DeltaTime, AAIController* Controller, APawn* Pawn);
	void Native_ReceiveTick(float DeltaTime, AAIController* Controller, APawn* Pawn);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveEnd(AAIController* AIController, APawn* OwnerPawn);
	void Native_ReceiveEnd(AAIController* AIController, APawn* OwnerPawn);
	
	UFUNCTION(BlueprintImplementableEvent)
	float EvaluateScore() const;


	
	
};