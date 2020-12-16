// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NLTCore.h"
#include "NLTUICore.h"
#include "Engine/GameInstance.h"
#include "NLTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NLT_API UNLTGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UNLTGameInstance();

	virtual void Init() override;


public:
	UFUNCTION(BlueprintPure,Category = NLTGameInstance)
	UNLTUICore* GetUICore()const{return UICore;}
	UFUNCTION(BlueprintPure,Category = NLTGameInstance)
	UNLTCore* GetNLTCore()const{return NLTCore;}
	UFUNCTION(BlueprintPure,Category = NLTGameInstance)
    UGlobalDispatcher* GetDispatcher()const{return Dispatcher;}
	//抽象出数据层
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=NLTGameInstance)
	TSubclassOf<UNLTUICore>BP_NLTUICore;
private:
	UPROPERTY()
	UNLTCore* NLTCore;
	UPROPERTY()
	UNLTUICore* UICore;
	UPROPERTY()
	UGlobalDispatcher* Dispatcher;
};
