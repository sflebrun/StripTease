/*
 * SparkleLEDs.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: Steven F. LeBrun
 */

#include "Colors.h"
#include "Interrupts.h"
#include "SparkleLEDs.h"

/**
 * The amount of time to delay between changes in the LEDs in milliseconds.
 */
const int SparkleLEDs::SPARKLE_DELAY = 100;

SparkleLEDs::SparkleLEDs(LedDevice * dLEDs ) :
	LightShow(dLEDs)
{

}

SparkleLEDs::~SparkleLEDs()
{

}

void SparkleLEDs::display()
{
	// Start the LED Device with just the default background color set.
	device->showBackground();
	CHECK_MODE_CHANGE;

	// Infinite Loop.  Exit when Change Mode Interrupt occurs.
	//Serial.println("Entering infinite Sparkle Loop");
	for ( ; ; )
	{
		CHECK_MODE_CHANGE;

		setColors( 80 );
		device->getDevice()->show();

		// Exits loop if Mode Change Interrupt has occurred.
		CHECK_MODE_CHANGE;

		delay( SPARKLE_DELAY );
	}
}

void SparkleLEDs::setColors( long percent )
{
	int  i;
	int  min     = 0;
	int  max     = 101;
	long rNum;

//	Serial.println("Entering setColor()");

	CRGB leds    = device->getLEDs();
	int  maxLEDs = device->numberOfLEDs();

	for ( i = 0 ; i < maxLEDs ; ++i )
	{
		rNum = random(min, max);

		if ( percent >= rNum )
		{
			device->setLED(i, Colors::randomJustColor());
		}
	}

	return;

}   // end of SparkleLEDs::setColors()

