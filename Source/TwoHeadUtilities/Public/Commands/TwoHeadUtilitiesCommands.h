#pragma once

#include "Framework/Commands/Commands.h"
#include "TwoHeadUtilitiesStyle.h"

class FTwoHeadUtilitiesCommands : public TCommands<FTwoHeadUtilitiesCommands>
{
public:
	FTwoHeadUtilitiesCommands()
		: TCommands(
			TEXT("TwoHeadUtilities"),
			NSLOCTEXT("Contexts", "TwoHeadUtilities", "TwoHeadUtilities Plugin"),
			NAME_None,
			FTwoHeadUtilitiesStyle::GetStyleSetName()
		)
	{
	}

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> PluginAction;
};
