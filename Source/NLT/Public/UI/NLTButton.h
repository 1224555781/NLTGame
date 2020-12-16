// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "RTTI/AnyType.h"

#include "NLTButton.generated.h"

/**
 * 
 */
UCLASS()
class NLT_API UNLTButton : public UButton
{
	GENERATED_BODY()

	public:
	FOnClicked NLTButtonOnClicked;
	TSharedPtr<SButton> GetSButton()
	{
		return MyButton;
	}

	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	void SetOnclickedDelegate(FOnClicked m_OnClicked)
	{
		if (MyButton.IsValid())
		{
			MyButton->SetOnClicked(m_OnClicked);
		}
		else
		{
			NLTButtonOnClicked = m_OnClicked;
		}
	}
};
