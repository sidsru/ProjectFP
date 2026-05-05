
// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ProjectFP : ModuleRules
{
    private string MySQLDirectory
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../MySQL/")); }
    }
	public ProjectFP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem",
            "StateTreeModule",
            "GameplayStateTreeModule",
            "HTTP",
            "Json",
            "JsonUtilities"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "OnlineSubsystemSteam",
            "UMG",
            "Slate",
            "SlateCore"
        });

        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(MySQLDirectory, "include"),
            Path.Combine(MySQLDirectory, "include/mysqlx"),
            Path.Combine(MySQLDirectory, "include/mysqlx/common"),
            Path.Combine(MySQLDirectory, "include/mysqlx/devapi"),
        });

        PublicAdditionalLibraries.AddRange(new string[]
        {
            Path.Combine(MySQLDirectory, "lib64/vs14/mysqlcppconnx.lib"),  // 주요 동적 라이브러리 연결을 위한 임포트 라이브러리
            Path.Combine(MySQLDirectory, "lib64/vs14/libcrypto.lib"),            // openSSL라이브러리
            Path.Combine(MySQLDirectory, "lib64/vs14/libssl.lib"),                // openSSL라이브러리
        });

        RuntimeDependencies.Add(
            "$(BinaryOutputDir)/mysqlcppconn-10-vs14.dll",
             Path.Combine(MySQLDirectory, "lib64/mysqlcppconn-10-vs14.dll"));

        RuntimeDependencies.Add(
            "$(BinaryOutputDir)/mysqlcppconnx-2-vs14.dll",
             Path.Combine(MySQLDirectory, "lib64/mysqlcppconnx-2-vs14.dll"));

        RuntimeDependencies.Add(
            "$(BinaryOutputDir)/libssl-3-x64.dll",
             Path.Combine(MySQLDirectory, "lib64/libssl-3-x64.dll"));

        RuntimeDependencies.Add(
            "$(BinaryOutputDir)/libcrypto-3-x64.dll",
             Path.Combine(MySQLDirectory, "lib64/libcrypto-3-x64.dll"));
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
