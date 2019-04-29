/*
 * LedRing.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: Steven F. LeBrun
 */

#include "LedRing.h"

const int   LedRing::RING_SIZE = LedRing_RING_SIZE;

LedRing::LedRing() :
	LedDevice(RING_SIZE, LedRing_DATA_PIN, ring)
{
	// NOTE: Must use a constant for the data pin in order for the template
	//       to compile properly.
	device.addLeds<NEOPIXEL, LedRing_DATA_PIN>(leds, maxLEDs);
}

LedRing::~LedRing()
{
	// TODO Auto-generated destructor stub
}

