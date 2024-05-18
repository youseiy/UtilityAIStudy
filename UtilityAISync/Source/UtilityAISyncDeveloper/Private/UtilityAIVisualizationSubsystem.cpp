// // Copyright Yousei. All Rights Reserved.



#include "UtilityAIVisualizationSubsystem.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "UtilitySync.h"
#include <imgui.h>
#include <vector>

#include "Runtime/AIModule/Classes/AIController.h"


void UUtilityAIVisualizationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
void UUtilityAIVisualizationSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Begin your ImGui window
	ImGui::Begin("UtilityAI Visualization Subsystem");

	// Iterate through all actors in the scene
	for (TObjectIterator<AAIController> It; It; ++It)
	{
		DebugUtility(*It);
	}

	// End ImGui window
	ImGui::End();
	
}

void UUtilityAIVisualizationSubsystem::DebugGAS(AActor* Actor)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Cast<AAIController>(Actor)->GetPawn()))
	{
		/// Display GAS Debug
		if (ImGui::CollapsingHeader("GAS"))
		{
			for (const auto& Element : ASC->GetOwnedGameplayTags())
			{
				ImGui::Text("Tag: %s",  TCHAR_TO_UTF8(*Element.ToString()));
			}
						
		}
	}
}

void UUtilityAIVisualizationSubsystem::DebugUtility(AActor* Actor)
{
	// If the UtilitySync component is valid, display actions and scores
	if (UUtilitySync* UtilitySyncComponent = Actor->FindComponentByClass<UUtilitySync>())
	{
		// Display actor's name in a collapsible header
		if (ImGui::CollapsingHeader(TCHAR_TO_UTF8(*Actor->GetActorNameOrLabel())))
		{
			ImGui::Indent();

			DebugGAS(Actor);
					
			// Display actor's name in a collapsible header
			if (ImGui::CollapsingHeader("Utility AI"))
			{
				// Iterate through utility actions and display their scores
				for (const auto& Action : UtilitySyncComponent->GetInstancedActions())
				{	
					ImGui::Text("Action: %s", TCHAR_TO_UTF8(*Action->GetFName().ToString()));
					//ImGui::SameLine();

					// Display the score value
					ImGui::Text("Score: %.2f", Action->EvaluateScore());
					
				}
			}
		}
	}
}

void UUtilityAIVisualizationSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

