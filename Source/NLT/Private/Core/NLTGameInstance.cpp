// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NLTGameInstance.h"



#include "Core/NLTLog.h"
#include "RTTI/GlobalDispatcher.h"

UNLTGameInstance::UNLTGameInstance()
{
    
}

void UNLTGameInstance::Init()
{
    Super::Init();
    MLBCoreLog(TEXT("GameInstace Init"));
    NLTCore = NewObject<UNLTCore>(this);
    NLTCore->Init();
    if (BP_NLTUICore)
        UICore = NewObject<UNLTUICore>(this,BP_NLTUICore);
    else
        UICore = NewObject<UNLTUICore>(this);
    UICore->Init(this);
    
    Dispatcher = NewObject<UGlobalDispatcher>(this);
    Dispatcher->Init();
    
}
