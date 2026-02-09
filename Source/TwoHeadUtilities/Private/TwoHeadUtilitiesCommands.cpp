// Copyright Epic Games, Inc. All Rights Reserved.

#include "TwoHeadUtilitiesCommands.h"

#define LOCTEXT_NAMESPACE "FTwoHeadUtilitiesModule"

void FTwoHeadUtilitiesCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TwoHeadUtilities", "Execute TwoHeadUtilities action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
