// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NLTButton.h"

#include "Core/NLTGameInstance.h"


TSharedRef<SWidget> UNLTButton::RebuildWidget()
{
	auto ret = Super::RebuildWidget();
	SetOnclickedDelegate(NLTButtonOnClicked);
	return ret;
}
