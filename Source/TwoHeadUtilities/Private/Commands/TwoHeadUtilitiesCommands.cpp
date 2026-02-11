// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#include "Commands/TwoHeadUtilitiesCommands.h"

#define LOCTEXT_NAMESPACE "FTwoHeadUtilitiesModule"

void FTwoHeadUtilitiesCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TwoHeadUtilities", "Execute TwoHeadUtilities action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
