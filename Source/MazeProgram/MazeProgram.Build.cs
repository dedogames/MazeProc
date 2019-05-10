/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************
     

	************************
	*    Improvements	   *
	************************
     

	************************
	*    Changes   	       *
	************************



	Date		 Developer			Description
	--------------------------------------------------


*/

using UnrealBuildTool;

public class MazeProgram : ModuleRules
{
	public MazeProgram(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
