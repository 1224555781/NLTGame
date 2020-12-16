// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetHandle.h"
#include "AssetHandleStyle.h"
#include "AssetHandleCommands.h"
#include "BatchProcessingTexture.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SScrollBox.h"

static const FName AssetHandleTabName("AssetHandle");

#define LOCTEXT_NAMESPACE "FAssetHandleModule"

void FAssetHandleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAssetHandleStyle::Initialize();
	FAssetHandleStyle::ReloadTextures();

	FAssetHandleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssetHandleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAssetHandleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetHandleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AssetHandleTabName, FOnSpawnTab::CreateRaw(this, &FAssetHandleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAssetHandleTabTitle", "AssetHandle"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);


	if (BPT == nullptr)
	{
		BPT = NewObject<UBatchProcessingTexture>();
	}
}

void FAssetHandleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetHandleStyle::Shutdown();

	FAssetHandleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AssetHandleTabName);
}

TSharedRef<SDockTab> FAssetHandleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText(
		LOCTEXT("WindowWidgetText", "Input Folder Iterator all 4k texture  batch to 1080")
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			/*// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]*/

			SNew(SScrollBox)
			+SScrollBox::Slot()
			[
				
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(EVerticalAlignment::VAlign_Top)
				[
				SNew(STextBlock)
				.Text(WidgetText)
				]
				+SVerticalBox::Slot()
                .VAlign(EVerticalAlignment::VAlign_Top)
                [
                	SNew(SHorizontalBox)
                	+SHorizontalBox::Slot()
                	
                	.HAlign(EHorizontalAlignment::HAlign_Fill)
                	[
					 SNew(/*BPT->EditableTextBox,*/SEditableTextBox)
					.Padding(FMargin(0,5,2,0))
					.HintText(FText::FromString(TEXT("Input Folder")))
					
					]
					+SHorizontalBox::Slot()
					.HAlign(EHorizontalAlignment::HAlign_Right)
					[
					SNew(SButton)
					.OnClicked_UObject(BPT,&UBatchProcessingTexture::ClickedButton)
					//.Text_UObject()
					
					
                	]
                	
                ]
				
				
			]
			

			
			
			
		];
}

void FAssetHandleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AssetHandleTabName);
}

void FAssetHandleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAssetHandleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAssetHandleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetHandleModule, AssetHandle)