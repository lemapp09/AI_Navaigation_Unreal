// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_Navigation : ModuleRules
{
	public AI_Navigation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core",
			"CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });
	}
}
