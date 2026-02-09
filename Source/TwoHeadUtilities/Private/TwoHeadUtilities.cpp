// Copyright Epic Games, Inc. All Rights Reserved.

#include "TwoHeadUtilities.h"
#include "TwoHeadUtilitiesStyle.h"
#include "TwoHeadUtilitiesCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName TwoHeadUtilitiesTabName("TwoHeadUtilities");

#define LOCTEXT_NAMESPACE "FTwoHeadUtilitiesModule"

void FTwoHeadUtilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	UE_LOG(LogTemp, Warning, TEXT("FTwoHeadUtilitiesModule::StartupModule"));
	
	FTwoHeadUtilitiesStyle::Initialize();
	FTwoHeadUtilitiesStyle::ReloadTextures();

	FTwoHeadUtilitiesCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTwoHeadUtilitiesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTwoHeadUtilitiesModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTwoHeadUtilitiesModule::RegisterMenus));
}

void FTwoHeadUtilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTwoHeadUtilitiesStyle::Shutdown();

	FTwoHeadUtilitiesCommands::Unregister();
	
	UE_LOG(LogTemp, Warning, TEXT("FTwoHeadUtilitiesModule::ShutdownModule"));
}

void FTwoHeadUtilitiesModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FTwoHeadUtilitiesModule::PluginButtonClicked()")),
							FText::FromString(TEXT("TwoHeadUtilities.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FTwoHeadUtilitiesModule::RegisterMenus()
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
	
IMPLEMENT_MODULE(FTwoHeadUtilitiesModule, TwoHeadUtilities)