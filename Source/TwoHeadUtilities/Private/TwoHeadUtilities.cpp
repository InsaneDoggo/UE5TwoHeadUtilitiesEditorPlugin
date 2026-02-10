#include "TwoHeadUtilities.h"
#include "TwoHeadUtilitiesStyle.h"
#include "EditorActions/FThuEditorActions.h"

void FTwoHeadUtilitiesModule::StartupModule()
{
	FTwoHeadUtilitiesStyle::Initialize();
	FTwoHeadUtilitiesStyle::ReloadTextures();

	EditorActions = MakeUnique<FThuEditorActions>();
	EditorActions->Initialize();
}

void FTwoHeadUtilitiesModule::ShutdownModule()
{
	EditorActions->Deinitialize();

	FTwoHeadUtilitiesStyle::Shutdown();
}

IMPLEMENT_MODULE(FTwoHeadUtilitiesModule, TwoHeadUtilities)
