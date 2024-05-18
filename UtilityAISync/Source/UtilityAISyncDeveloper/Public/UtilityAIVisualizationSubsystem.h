// // Copyright Yousei. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UtilityAIVisualizationSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAISYNCDEVELOPER_API UUtilityAIVisualizationSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
    
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}

	void DebugGAS(AActor* Actor);

	void DebugUtility(AActor* Actor);
};
