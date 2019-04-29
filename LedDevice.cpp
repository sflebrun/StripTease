/*
 *  Created on: Jan 17, 2019
 *     Author:  Steven F. LeBrun
 */

#include <FastLED.h>

#include "LedDevice.h"

LedDevice::LedDevice(int nLEDs, int dPin, CRGB *lights) :
	maxLEDs(nLEDs), dataPin(dPin), leds(lights), foreground(CRGB::Yellow), background(CRGB::Cyan)
{
}

LedDevice::~LedDevice()
{
}

void LedDevice::advanceLEDs()
{
  int i;

  for ( i = maxLEDs - 1 ; i > 0 ; --i )
  {
    leds[i] = leds[i - 1];
  }

  leds[0] = background;

}

void LedDevice::retreatLEDs()
{
	int i;

	for ( i = 1 ; i < maxLEDs ; ++i )
	{
		leds[i - 1] = leds[i];
	}

	leds[maxLEDs - 1] = background;
}

void LedDevice::showBackground()
{
	setLEDsBackground();
	device.show();
}

void LedDevice::showForeground()
{
	setLEDsForeground();
	device.show();
}

void LedDevice::setBackground( CRGB color )
{
	background = color;
}

void LedDevice::setForeground( CRGB color )
{
	foreground = color;
}

void LedDevice::setLEDsBackground()
{
	setLEDs(background);
}

void LedDevice::setLEDsForeground()
{
	setLEDs(foreground);
}

void LedDevice::setLEDs(CRGB color)
{
	int i;

	for ( i = 0 ; i < maxLEDs ; ++i )
	{
		leds[i] = color;
	}
}



