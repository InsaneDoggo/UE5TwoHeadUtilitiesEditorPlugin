#pragma once

#include "Modules/ModuleManager.h"

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
};
