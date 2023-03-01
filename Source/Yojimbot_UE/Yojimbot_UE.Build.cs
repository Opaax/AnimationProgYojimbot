// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Yojimbot_UE : ModuleRules
{
	public Yojimbot_UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "ControlRig" });
	}
}
