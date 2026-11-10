// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"

class SPECTESTBASE_API ColourHelper
{
public:
	ColourHelper();
	~ColourHelper();

	static FLinearColor RGB2BGR(const FLinearColor& inputCol);
};
