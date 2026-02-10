#pragma once

class FThuEditorActions
{
public:
	void Initialize();
	void Deinitialize();
	
	void PluginButtonClicked();
	
private:
	void RegisterMenus();
	
	TSharedPtr<FUICommandList> PluginCommands;	
};
