// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Brainslol : ModuleRules
{
	public Brainslol(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Http", "Json", "JsonUtilities", "Networking", "OnlineSubsystem", "OnlineSubsystemUtils" });


        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG", "Http", "Json", "JsonUtilities", "Networking" });


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
