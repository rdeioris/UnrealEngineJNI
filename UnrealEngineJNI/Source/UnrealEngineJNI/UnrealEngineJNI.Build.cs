// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class UnrealEngineJNI : ModuleRules
{

    // leave it null for using JAVA_HOME environment variable
    private string javaHome = null;

    public UnrealEngineJNI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (javaHome == null)
        {
            javaHome = Environment.GetEnvironmentVariable("JAVA_HOME");
            if (javaHome == null)
            {
                Console.WriteLine("JAVA_HOME is not set, compilation will fail...");
            }
        }

        if (javaHome != null)
        {

            Console.WriteLine("Using JAVA_HOME={0}", javaHome);

            if (!Directory.Exists(javaHome))
            {
                Console.WriteLine("The JAVA_HOME directory does not exist, compilation will fail...");
            }
        }

        PublicIncludePaths.AddRange(
            new string[] {
                "UnrealEngineJNI/Public"
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "UnrealEngineJNI/Private",
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Add the import library
            PublicLibraryPaths.Add(Path.Combine(javaHome, "lib"));
            PublicAdditionalLibraries.Add("jvm.lib");


            PublicIncludePaths.Add(Path.Combine(javaHome, "include"));
            PublicIncludePaths.Add(Path.Combine(javaHome, "include", "win32"));
        }


    }
}
