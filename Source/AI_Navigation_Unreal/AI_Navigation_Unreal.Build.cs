// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_Navigation_Unreal : ModuleRules
{
	public AI_Navigation_Unreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
