// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetHandleCommands.h"

#define LOCTEXT_NAMESPACE "FAssetHandleModule"

void FAssetHandleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AssetHandle", "Bring up AssetHandle window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
