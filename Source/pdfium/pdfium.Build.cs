// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class pdfium : ModuleRules
{
	public pdfium(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
    
    bool isLibrarySupported = false;

    if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
    {
        isLibrarySupported = true;

        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
        string LibrariesPath = Path.Combine(ThirdPartyPath, "pdfiumlib", "Libraries");

        PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "x64", "pdfium.dll.lib"));
    }

    //if (isLibrarySupported)
    //{
        // Include path
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "pdfiumlib", "Includes"));
    //}

    PublicDefinitions.Add(string.Format("WITH_PDFIUM_BINDING={0}", isLibrarySupported ? 1 : 0));


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
  
  private string ModulePath
  {
      get { return ModuleDirectory; }
  }

  private string ThirdPartyPath
  {
      get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
  }

}
