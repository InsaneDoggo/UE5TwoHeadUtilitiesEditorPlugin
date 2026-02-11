// Copyright (c) 2026 InsaneDoggo. All rights reserved.

#pragma once

class FThuEditorActions
{
public:
	void Initialize();
	void Deinitialize();
	
	void OnAction_SelectHismParent();
	
private:	
	TSharedPtr<FUICommandList> PluginCommands;	
};
