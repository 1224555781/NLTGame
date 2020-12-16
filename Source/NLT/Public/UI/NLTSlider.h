// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "Core/NLTDataTypes.h"
#include "RTTI/AnyType.h"

#include "NLTSlider.generated.h"

/**
 * 
 */
UCLASS(meta=( DisplayName="Slider (NLT)"))
class NLT_API UNLTSlider : public USlider
{
	GENERATED_UCLASS_BODY()
	public:
	//UNLTSlider(const FObjectInitializer& ObjectInitializer);
	void SetEventDelegate(const AnyType& event);

	FSliderStatChanged SliderStatChanged;
	

	protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
