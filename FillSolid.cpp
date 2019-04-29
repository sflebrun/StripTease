/*
 * FillSolid.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Steven F. LeBrun
 */

#include "FillSolid.h"

FillSolid::FillSolid(CRGB fColor, CRGB bColor, LedDevice * dLED) :
	FillAndClear(dLED), foreground(fColor), background(bColor)
{
}

FillSolid::~FillSolid()
{
}

CRGB FillSolid::nextColor(int offset)
{
	CRGB color = ( offset < maxLEDs ) ? foreground : background ;

	return color;
}

void FillSolid::setForeground( CRGB fColor )
{
	foreground = fColor;
}

void FillSolid::setBackground( CRGB bColor )
{
	background = bColor;
}

