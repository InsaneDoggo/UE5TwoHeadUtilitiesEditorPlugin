// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "TwoHeadUtilitiesStyle.h"

class FTwoHeadUtilitiesCommands : public TCommands<FTwoHeadUtilitiesCommands>
{
public:

	FTwoHeadUtilitiesCommands()
		: TCommands<FTwoHeadUtilitiesCommands>(TEXT("TwoHeadUtilities"), NSLOCTEXT("Contexts", "TwoHeadUtilities", "TwoHeadUtilities Plugin"), NAME_None, FTwoHeadUtilitiesStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
