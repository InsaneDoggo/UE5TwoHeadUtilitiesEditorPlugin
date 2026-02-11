// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThuPluginEditorSettingsPage.generated.h"

/**
 * Editor Settings Page for plugin
 */
UCLASS(config=Editor, meta=(DisplayName="Two Head Utilities"))
class UThuPluginEditorSettingsPage : public UObject
{
	GENERATED_BODY()

public:
	UThuPluginEditorSettingsPage(const FObjectInitializer& Initializer);

	UPROPERTY(config, EditAnywhere, Category=General, Meta=(ConfigRestartRequired=false, DisplayName="Test Bool"))
	bool bEnabled;
};


class FSettingsManager
{
public:
	void Initialize();
	void Deinitialize();

private:
	TSharedPtr<class ISettingsSection> SettingsSection;
};
