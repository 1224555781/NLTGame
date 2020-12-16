// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AssetHandleStyle.h"

class FAssetHandleCommands : public TCommands<FAssetHandleCommands>
{
public:

	FAssetHandleCommands()
		: TCommands<FAssetHandleCommands>(TEXT("AssetHandle"), NSLOCTEXT("Contexts", "AssetHandle", "AssetHandle Plugin"), NAME_None, FAssetHandleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};