// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EnemyGame : ModuleRules
{
	public EnemyGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput",
			"MotionWarping"
		} );

		PublicIncludePaths.Add("EnemyGame/");// Add our project to include directories

		PrivateDependencyModuleNames.AddRange( new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" } );


	}
}
