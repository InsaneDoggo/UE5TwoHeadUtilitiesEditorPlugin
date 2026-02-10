#include "FThuEditorActions.h"
#include "LevelEditorSubsystem.h"
#include "Commands/TwoHeadUtilitiesCommands.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Elements/Framework/TypedElementSelectionSet.h"
#include "Elements/SMInstance/SMInstanceElementData.h"

#define LOCTEXT_NAMESPACE "FTwoHeadUtilitiesModule"

void FThuEditorActions::Initialize()
{
	FTwoHeadUtilitiesCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTwoHeadUtilitiesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FThuEditorActions::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FThuEditorActions::RegisterMenus));
}

void FThuEditorActions::Deinitialize()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	
	FTwoHeadUtilitiesCommands::Unregister();
}

void FThuEditorActions::PluginButtonClicked()
{	
	UE_LOG(LogTemp, Warning, TEXT("THUCommandManager::PluginButtonClicked"));
	
	if (!GEditor) return;

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

void FThuEditorActions::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTwoHeadUtilitiesCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTwoHeadUtilitiesCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
