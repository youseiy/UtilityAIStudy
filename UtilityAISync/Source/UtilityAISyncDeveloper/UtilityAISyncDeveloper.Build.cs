using UnrealBuildTool;

public class UtilityAISyncDeveloper : ModuleRules
{
    public UtilityAISyncDeveloper(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "ImGui",
                "UtilityAISync", "UtilityAISync","GameplayAbilities","AIModule",
            }
        );
    }
}