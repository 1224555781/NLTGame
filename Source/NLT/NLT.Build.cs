// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class NLT : ModuleRules
{
	
	private string MySqlPath
	{
		get
		{

			return Path.Combine( "ThirdParty/SQL");
		}

	}
	public NLT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//PublicIncludePaths.Add(Path.Combine(PluginDirectory,"ThirdParty/SQL/include"));
		string SQLPubilcInclude = Path.Combine(MySqlPath ,"include");
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				//"Editor/AnimGraph",
				SQLPubilcInclude
			}
		);
		
		//bEnableExceptions = true;
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"PhysicsCore",
			"PhysX",
			"UMG",
			"NavigationSystem",
			"AIModule",
			"GameplayTags",
			"GameplayTasks",
			"ApexDestruction",
			"Json",
			"Sequencer",
			"Niagara"	//,
			//"GameplayAbilities"
			
		});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"InputCore",
				"RHI",
				"RenderCore",
				"NetworkReplayStreaming",
				"AIModule",
				
				"GameplayTags",
				"PhysXVehicles"

			});

		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string SQLLib = Path.Combine(MySqlPath ,"lib64");
			
			PublicLibraryPaths.Add(SQLLib);
			PublicAdditionalLibraries.Add("libmysqlcppconn8-static.a");
			PublicDelayLoadDLLs.Add("libmysqlcppconn8.so");
			RuntimeDependencies.Add(new RuntimeDependency("$(ProjectDir)/Binaries/Win64/libmysqlcppconn8.so"));
		}
	}
}
