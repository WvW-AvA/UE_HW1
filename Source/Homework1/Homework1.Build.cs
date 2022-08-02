// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Homework1 : ModuleRules
{
	public Homework1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {"SlateCore", "Slate", "UMG", "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
    }
}
