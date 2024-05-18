// // Copyright Yousei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "UtilityAIBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAISYNC_API UUtilityAIBlueprintLibrary : public UObject
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable,BlueprintPure,Category=UtilityAIBlueprintLibrary)
	static float GetFloatFromBlackboard(FGameplayTag ValueTag,class UBlackboard* Blackboard );
	UFUNCTION(BlueprintCallable,BlueprintPure,Category=UtilityAIBlueprintLibrary)
	static int32 GetIntFromBlackboard(FGameplayTag ValueTag,class UBlackboard* Blackboard );
	UFUNCTION(BlueprintCallable,BlueprintPure,Category=UtilityAIBlueprintLibrary)
	static bool GetBoolFromBlackboard(FGameplayTag ValueTag,class UBlackboard* Blackboard );
	UFUNCTION(BlueprintCallable,BlueprintPure,Category=UtilityAIBlueprintLibrary)
	static AActor* GetActorFromBlackboard(FGameplayTag ValueTag,class UBlackboard* Blackboard );

	
	UFUNCTION(BlueprintCallable,Category=UtilityAIBlueprintLibrary)
	static void SetFloatFromBlackboard(FGameplayTag ValueTag,float Value,class UBlackboard* Blackboard );
	UFUNCTION(BlueprintCallable,Category=UtilityAIBlueprintLibrary)
	static void SetIntFromBlackboard(FGameplayTag ValueTag,int32 Value,class UBlackboard* Blackboard );
	UFUNCTION(BlueprintCallable,Category=UtilityAIBlueprintLibrary)
	static void SetBoolFromBlackboard(FGameplayTag ValueTag,bool Value,class UBlackboard* Blackboard );
	UFUNCTION(BlueprintCallable,Category=UtilityAIBlueprintLibrary)
	static void SetActorFromBlackboard(FGameplayTag ValueTag,AActor* Value,class UBlackboard* Blackboard );
	
	
	
};
