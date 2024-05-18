// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InstancedStruct.h"
#include "UtilityAchtypeConfig.generated.h"



UCLASS()
class UTILITYAISYNC_API UUtilityArchetypeConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TMap<FGameplayTag,TSoftClassPtr<class UUtilityAction>> UtilityActions;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TMap<FGameplayTag,FRuntimeFloatCurve> UtilityConsiderations;

	
	
};
