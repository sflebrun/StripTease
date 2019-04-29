/*
 * Colors.cpp
 *
 * Defines the variables and methods of the Colors class.
 *
 *  Created on: Jan 18, 2019
 *      Author: Steven F. LeBrun
 */

#include "Colors.h"

const CRGB  Colors::allColors[] =
				{
						CRGB::Black,
						CRGB::White,
						CRGB::Red,
						CRGB::Yellow,
						CRGB::Green,
						CRGB::Cyan,
						CRGB::Blue,
						CRGB::Purple
				};

const   int Colors::MAX_ALL_COLORS  = sizeof(allColors) / sizeof(CRGB);
const   int Colors::MAX_NO_BLACK    = MAX_ALL_COLORS - 1;
const   int Colors::MAX_JUST_COLORS = MAX_ALL_COLORS - 2;


Colors::Colors()
{

}

Colors::~Colors()
{

}


CRGB  Colors::randomJustColor()
{
	long offset = random(MAX_JUST_COLORS);

	CRGB nextColor = allColors[offset + 2];

	return nextColor;
}

CRGB  Colors::randomAllColor()
{
	CRGB nextColor = allColors[random(MAX_ALL_COLORS)];

	return nextColor;
}

CRGB  Colors::randomNoBlack()
{
	CRGB nextColor = noBlack[random(MAX_NO_BLACK)];

	return nextColor;
}

CRGB  Colors::nextColor()
{
	++cnt;
	if ( cnt >= MAX_JUST_COLORS )
	{
		cnt = 0;
	}

	return getJustColor(cnt);
}



