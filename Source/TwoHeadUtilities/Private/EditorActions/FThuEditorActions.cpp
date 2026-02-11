// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#include "FThuEditorActions.h"

#include "LevelEditor.h"
#include "LevelEditorSubsystem.h"
#include "Selection.h"
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
		FExecuteAction::CreateRaw(this, &FThuEditorActions::OnAction_SelectHismParent),
		FCanExecuteAction());

	// Add support for Viewport hotkeys	
	TSharedPtr<FUICommandList> CommandList = GetLevelEditorModule().GetGlobalLevelEditorActions();

	CommandList->MapAction(
		FTwoHeadUtilitiesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FThuEditorActions::OnAction_SelectHismParent),
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

void FThuEditorActions::OnAction_SelectHismParent()
{
	UE_LOG(LogTemp, Warning, TEXT("FThuEditorActions::OnAction_SelectHismParent"));

	if (!GEditor) return;

	// Test Settings
	UThuPluginEditorSettingsPage* SettingsPage = GetMutableDefault<UThuPluginEditorSettingsPage>();
	UE_LOG(LogTemp, Warning, TEXT("SettingsPage: %s"), SettingsPage->bEnabled ? TEXT("Enabled") : TEXT("Disabled"));

	UTypedElementSelectionSet* SelectionSet = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>()->GetSelectionSet();
	if (!SelectionSet)
	{
		UE_LOG(LogTemp, Error, TEXT("SelectionSet is NULL"));
		return;
	}

	TArray<FScriptTypedElementHandle> SelectedElementHandles = SelectionSet->K2_GetSelectedElementHandles();

	bool bFoundHismComponent = false;
	AActor* ActorToSelect = nullptr;

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

		bFoundHismComponent = true;
		auto* InstancedStaticMeshComponent = SMInstance.GetISMComponent();

		UE_LOG(LogTemp, Warning, TEXT("Selected ISM Component: %s"), *InstancedStaticMeshComponent->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Selected ISM Parent: %s"), *InstancedStaticMeshComponent->GetOwner()->GetName());

		ActorToSelect = InstancedStaticMeshComponent->GetOwner();
	}

	if (!bFoundHismComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("HierarchicalInstancedStaticMeshComponent wasn't found in selection set"));
	}

	if (ActorToSelect)
	{
		const FScopedTransaction Transaction(LOCTEXT("ClickingOnActor", "Clicking on Actor in Data Layer"));
		GEditor->GetSelectedActors()->Modify();
		GEditor->SelectNone(false, true);
		GEditor->SelectActor(ActorToSelect, true,true, true);
		GEditor->NoteSelectionChange();
		// GEditor->MoveViewportCamerasToActor(*ActorToSelect, /*bActiveViewportOnly*/false);
	}
}

#undef LOCTEXT_NAMESPACE
