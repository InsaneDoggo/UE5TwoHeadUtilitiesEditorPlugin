#include "TwoHeadUtilitiesStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FTwoHeadUtilitiesStyle::StyleInstance = nullptr;

void FTwoHeadUtilitiesStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTwoHeadUtilitiesStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FTwoHeadUtilitiesStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TwoHeadUtilitiesStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FTwoHeadUtilitiesStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("TwoHeadUtilitiesStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TwoHeadUtilities")->GetBaseDir() / TEXT("Resources"));

	Style->Set("TwoHeadUtilities.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FTwoHeadUtilitiesStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTwoHeadUtilitiesStyle::Get()
{
	return *StyleInstance;
}
