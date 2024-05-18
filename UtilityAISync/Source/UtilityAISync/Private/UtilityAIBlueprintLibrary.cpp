// // Copyright Yousei. All Rights Reserved.


#include "UtilityAIBlueprintLibrary.h"

#include "Blackboard.h"

float UUtilityAIBlueprintLibrary::GetFloatFromBlackboard(FGameplayTag ValueTag, UBlackboard* Blackboard)
{
	if (!Blackboard) return 0.f;
	
	return Blackboard->GetValue<float>(ValueTag);
}

int32  UUtilityAIBlueprintLibrary::GetIntFromBlackboard(FGameplayTag ValueTag, UBlackboard* Blackboard)
{
	if (!Blackboard) return 0.f;
	return Blackboard->GetValue<int32>(ValueTag);
}

bool UUtilityAIBlueprintLibrary::GetBoolFromBlackboard(FGameplayTag ValueTag, UBlackboard* Blackboard)
{
	if (!Blackboard) return false;
	return Blackboard->GetValue<bool>(ValueTag);
}

AActor* UUtilityAIBlueprintLibrary::GetActorFromBlackboard(FGameplayTag ValueTag, UBlackboard* Blackboard)
{
	if (!Blackboard) return nullptr;
	return Blackboard->GetValue<AActor*>(ValueTag);
}

void UUtilityAIBlueprintLibrary::SetFloatFromBlackboard(FGameplayTag ValueTag, float Value, UBlackboard* Blackboard)
{
	if (!Blackboard) return ;
	Blackboard->SetValue<float>(ValueTag,Value);
}

void UUtilityAIBlueprintLibrary::SetIntFromBlackboard(FGameplayTag ValueTag, int32 Value, UBlackboard* Blackboard)
{
	if (!Blackboard) return ;
	Blackboard->SetValue<int32 >(ValueTag,Value);
}

void UUtilityAIBlueprintLibrary::SetBoolFromBlackboard(FGameplayTag ValueTag, bool Value, UBlackboard* Blackboard)
{
	if (!Blackboard) return;
	Blackboard->SetValue<bool >(ValueTag,Value);
}

void UUtilityAIBlueprintLibrary::SetActorFromBlackboard(FGameplayTag ValueTag, AActor* Value,
	UBlackboard* Blackboard)
{
	if (!Blackboard) return;
	Blackboard->SetValue<AActor*>(ValueTag,Value);
}
