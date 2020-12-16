// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/NLTUtilityFunctionLibrary.h"

#include "Core/NLTCore.h"
#include "Core/NLTGameInstance.h"
#include "Kismet/GameplayStatics.h"

UNLTCore* UNLTUtilityFunctionLibrary::GetNLTCore(const UObject* WorldContextObject)
{
    if(!WorldContextObject)
        return nullptr;
    UNLTGameInstance* GI = Cast<UNLTGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
    return  GI->GetNLTCore();
}

UGlobalDispatcher* UNLTUtilityFunctionLibrary::GetDispatcher(const UObject* WorldContextObject)
{
    if(!WorldContextObject)
        return nullptr;
    UNLTGameInstance* GI = Cast<UNLTGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
    return GI->GetDispatcher();
}

