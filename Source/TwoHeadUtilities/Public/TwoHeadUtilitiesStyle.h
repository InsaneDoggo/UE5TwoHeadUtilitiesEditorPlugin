// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#pragma once

#include "Styling/SlateStyle.h"

class FTwoHeadUtilitiesStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static void ReloadTextures();

	static const ISlateStyle& Get();
	static FName GetStyleSetName();

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
