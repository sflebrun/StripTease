/*
 * LedStrip.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: Steven F. LeBrun
 */

#include "LedStrip.h"

const int   LedStrip::STRIP_SIZE = LedStrip_STRIP_SIZE;

LedStrip::LedStrip() :
	LedDevice(STRIP_SIZE, LedStrip_DATA_PIN, strip)
{
	device.addLeds<NEOPIXEL, LedStrip_DATA_PIN>(leds, maxLEDs);
}

LedStrip::~LedStrip()
{

}

