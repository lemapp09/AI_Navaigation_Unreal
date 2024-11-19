// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_Navagation_UnReal : ModuleRules
{
	public AI_Navagation_UnReal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
