// // Copyright Yousei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include <type_traits> // For static_assert
#include <memory> // For std::shared_ptr
#include "Blackboard.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UTILITYAISYNC_API UBlackboard : public UObject
{
	GENERATED_BODY()
	
	// Internal storage for key-value pairs
	
	TMap<FGameplayTag, TSharedPtr<void>> BlackboardData;

public:
	
	// Template function to get a value from the blackboard
	template<typename T>
	T GetValue(const FGameplayTag& Key) const
	{
		//static_assert(!std::is_pointer<T>::value, "Use of raw pointers is not allowed. Use smart pointers instead.");

		if (auto ValuePtr = BlackboardData.Find(Key))
		{
			return *StaticCastSharedPtr<T>(*ValuePtr);
		}
		// Return default value if key not found
		return T{};
	}

	// Template function to set a value in the blackboard
	template<typename T>
	void SetValue(const FGameplayTag& Key, const T& Value)
	{
		//static_assert(!std::is_pointer<T>::value, "Use of raw pointers is not allowed. Use smart pointers instead.");
        
		BlackboardData.Add(Key, MakeShared<T>(Value));
	}


};
