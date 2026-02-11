// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FSettingsManager;
class ISettingsSection;
class FToolBarBuilder;
class FMenuBuilder;
class FThuEditorActions;

class FTwoHeadUtilitiesModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;	

private:
	TUniquePtr<FThuEditorActions> EditorActions;
	TUniquePtr<FSettingsManager> SettingsManager;
};
