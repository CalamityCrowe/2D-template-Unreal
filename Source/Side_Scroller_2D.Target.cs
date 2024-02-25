// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Side_Scroller_2DTarget : TargetRules
{
	public Side_Scroller_2DTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest; 
		ExtraModuleNames.AddRange( new string[] { "Side_Scroller_2D" } );
	}
}
