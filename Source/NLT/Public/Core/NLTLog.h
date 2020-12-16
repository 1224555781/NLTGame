// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


DECLARE_LOG_CATEGORY_EXTERN(MLBCore,Log,All);
DECLARE_LOG_CATEGORY_EXTERN(MLBUI,Log,All);
#define print(text)  GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::White,text);

/**
 * 
 */



static void MLBCoreLog(const FString& LogContent,bool bPrint = false,ELogVerbosity::Type MLBLogType  = ELogVerbosity::Type::Log)
{
#if bPrint && !UE_BUILD_SHIPPING
    print(LogContent);
#endif
    switch (MLBLogType)
    {
   
    case ELogVerbosity::Fatal:
        UE_LOG(MLBCore,Fatal,TEXT("%s"),*LogContent);
        break;
    case ELogVerbosity::Error:
        UE_LOG(MLBCore,Error,TEXT("%s"),*LogContent);
        break;
    case ELogVerbosity::Warning:
        UE_LOG(MLBCore,Warning,TEXT("%s"),*LogContent);
        break;
    case ELogVerbosity::Display: break;
    case ELogVerbosity::Log:
        UE_LOG(MLBCore,Log,TEXT("%s"),*LogContent);
        break;
    
    default: ;
    }
   
   
}

static void MLBUILog(const FString& LogContent,bool bPrint = false,ELogVerbosity::Type MLBLogType  = ELogVerbosity::Type::Log)
{
#if bPrint && !UE_BUILD_SHIPPING
    print(LogContent);
#endif
    switch (MLBLogType)
    {
   
    case ELogVerbosity::Fatal:
        UE_LOG(MLBUI,Fatal,TEXT("%s"),*LogContent);
        break;
    case ELogVerbosity::Error:
        UE_LOG(MLBUI,Error,TEXT("%s"),*LogContent);
        break;
    case ELogVerbosity::Warning:
        UE_LOG(MLBCore,Warning,TEXT("%s"),*LogContent);
        break;
    case ELogVerbosity::Display: break;
    case ELogVerbosity::Log:
        UE_LOG(MLBUI,Log,TEXT("%s"),*LogContent);
        break;
    
    default: ;
    }
   
   
}
