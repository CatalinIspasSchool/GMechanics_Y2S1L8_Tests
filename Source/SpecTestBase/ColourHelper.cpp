// Fill out your copyright notice in the Description page of Project Settings.


#include "ColourHelper.h"

ColourHelper::ColourHelper()
{
}

ColourHelper::~ColourHelper()
{
}

FLinearColor ColourHelper::RGB2BGR(const FLinearColor& inputCol)
{
	FLinearColor outputCol(inputCol);

	outputCol.R = inputCol.B;
	outputCol.B = inputCol.R;

	return outputCol;
}
