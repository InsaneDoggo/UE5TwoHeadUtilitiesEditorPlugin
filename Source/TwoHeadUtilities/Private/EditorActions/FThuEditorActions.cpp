// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#include "FThuEditorActions.h"

#include "LevelEditor.h"
#include "LevelEditorSubsystem.h"
#include "Commands/TwoHeadUtilitiesCommands.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Elements/Framework/TypedElementSelectionSet.h"
#include "Elements/SMInstance/SMInstanceElementData.h"
#include "SettingsPage/ThuPluginEditorSettingsPage.h"

#define LOCTEXT_NAMESPACE "FTwoHeadUtilitiesModule"

static FLevelEditorModule& GetLevelEditorModule()
{
	return FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
}

void FThuEditorActions::Initialize()
{
	FTwoHeadUtilitiesCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTwoHeadUtilitiesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FThuEditorActions::PluginButtonClicked),
		FCanExecuteAction());

	// Add support for Viewport hotkeys	
	TSharedPtr<FUICommandList> CommandList = GetLevelEditorModule().GetGlobalLevelEditorActions();
	
	CommandList->MapAction(
		FTwoHeadUtilitiesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FThuEditorActions::PluginButtonClicked),
		FCanExecuteAction()
	);
}

void FThuEditorActions::Deinitialize()
{	
	// Remove support for Viewport hotkeys
	TSharedPtr<FUICommandList> CommandList = GetLevelEditorModule().GetGlobalLevelEditorActions();
	CommandList->UnmapAction(FTwoHeadUtilitiesCommands::Get().PluginAction);
		
	FTwoHeadUtilitiesCommands::Unregister();
}

void FThuEditorActions::PluginButtonClicked()
{	
	UE_LOG(LogTemp, Warning, TEXT("THUCommandManager::PluginButtonClicked"));
	
	if (!GEditor) return;
	
	// Test Settings
	UThuPluginEditorSettingsPage* DevSettings = GetMutableDefault<UThuPluginEditorSettingsPage>();
	UE_LOG(LogTemp, Warning, TEXT("DevSettings: %s"), DevSettings->bEnabled ? TEXT("Enabled") : TEXT("Disabled"));

	UTypedElementSelectionSet* SelectionSet = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>()->GetSelectionSet();
	if (!SelectionSet) return;

	TArray<FScriptTypedElementHandle> SelectedElementHandles = SelectionSet->K2_GetSelectedElementHandles();

	for (auto ElementHandle : SelectedElementHandles)
	{
		if (!ElementHandle.IsSet())
		{
			continue;
		}

		auto TypedElementHandle = ElementHandle.GetTypedElementHandle();
		const auto SMInstance = SMInstanceElementDataUtil::GetSMInstanceFromHandle(TypedElementHandle, true);

		if (!SMInstance)
		{
			continue;
		}

		auto* InstancedStaticMeshComponent = SMInstance.GetISMComponent();

		UE_LOG(LogTemp, Warning, TEXT("Selected ISM Component: %s"), *InstancedStaticMeshComponent->GetName());
	}
}

#undef LOCTEXT_NAMESPACE
