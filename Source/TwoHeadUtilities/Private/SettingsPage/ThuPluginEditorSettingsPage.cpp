// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#include "SettingsPage/ThuPluginEditorSettingsPage.h"
#include "ISettingsModule.h"

#define CONTAINER_NAME "Editor"
#define CATEGORY_NAME "General"
#define SECTION_NAME "Two Head Utilities"

#define LOCTEXT_NAMESPACE "TwoHeadUtilities"

UThuPluginEditorSettingsPage::UThuPluginEditorSettingsPage(const FObjectInitializer& Initializer)
{
}

static ISettingsModule* GetSettingsModule() { return FModuleManager::GetModulePtr<ISettingsModule>("Settings"); }

void FSettingsManager::Initialize()
{
	auto* SettingsModule = GetSettingsModule();
	if (!SettingsModule) return;

	SettingsSection = SettingsModule->RegisterSettings(
		CONTAINER_NAME, CATEGORY_NAME, SECTION_NAME,
		LOCTEXT("ThuSettingsPageName", "Two Head Utilities"),
		LOCTEXT("ThuSettingsPageDescription", "Settings for 'Two Head Utilities' plugin"),
		GetMutableDefault<UThuPluginEditorSettingsPage>()
	);
}

void FSettingsManager::Deinitialize()
{
	auto* SettingsModule = GetSettingsModule();
	if (!SettingsModule) return;
	
	SettingsModule->UnregisterSettings(CONTAINER_NAME, CATEGORY_NAME, SECTION_NAME);
}

#undef LOCTEXT_NAMESPACE
