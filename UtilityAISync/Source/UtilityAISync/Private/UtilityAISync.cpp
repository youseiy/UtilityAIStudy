// Copyright Epic Games, Inc. All Rights Reserved.

#include "UtilityAISync.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "FUtilityAISyncModule"

void FUtilityAISyncModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if WITH_EDITOR 
	FModuleManager::LoadModulePtr< IModuleInterface >("AITestSuite");

	if (GIsEditor)
	{
		// Register asset types
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		// register AI category so that AI assets can register to it
		AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("UtilityAI")), LOCTEXT("UtilityAI", "UtilityAI"));
	}
#endif // WITH_EDITOR 
}

void FUtilityAISyncModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUtilityAISyncModule, UtilityAISync)