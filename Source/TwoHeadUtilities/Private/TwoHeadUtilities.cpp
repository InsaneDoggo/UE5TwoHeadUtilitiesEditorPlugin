// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#include "TwoHeadUtilities.h"
#include "TwoHeadUtilitiesStyle.h"
#include "EditorActions/FThuEditorActions.h"
#include "SettingsPage/ThuPluginEditorSettingsPage.h"

void FTwoHeadUtilitiesModule::StartupModule()
{
	FTwoHeadUtilitiesStyle::Initialize();
	FTwoHeadUtilitiesStyle::ReloadTextures();

	EditorActions = MakeUnique<FThuEditorActions>();
	EditorActions->Initialize();
	
	SettingsManager = MakeUnique<FSettingsManager>();
	SettingsManager->Initialize();
}

void FTwoHeadUtilitiesModule::ShutdownModule()
{
	SettingsManager->Deinitialize();
	EditorActions->Deinitialize();
	
	FTwoHeadUtilitiesStyle::Shutdown();
}

IMPLEMENT_MODULE(FTwoHeadUtilitiesModule, TwoHeadUtilities)
