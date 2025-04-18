// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SharedCoolingTest : ModuleRules
{
	public SharedCoolingTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
 			"GameplayTags",
 			"GameplayTasks",
 			"GameplayAbilities",
            "SharedCoolingAbility",
        });
	}
}
