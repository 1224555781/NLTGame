// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/NLTCore.h"
#include "Core/NLTUICore.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NLTUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NLT_API UNLTUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	UFUNCTION(Category=UtilityFunctionLibrary,BlueprintPure,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
	static UNLTCore* GetNLTCore(const UObject* WorldContextObject);

	UFUNCTION(Category=UtilityFunctionLibrary,BlueprintPure,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
	static UGlobalDispatcher* GetDispatcher(const UObject* WorldContextObject);
};
