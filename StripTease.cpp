/*
 * StripTease.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: Steven F. LeBrun
 */

#include <Arduino.h>
#include <FastLED.h>

#include "Colors.h"
#include "Interrupts.h"
#include "LedRing.h"
#include "LedStrip.h"

#include "FillSolid.h"
#include "SparkleLEDs.h"
#include "Sweeper.h"

#define  INTR_PIN     2
#define  INTR         INT0

#define  STRIP_DATA_PIN  6
#define  RING_DATA_PIN   5
#define  UNUSED_PIN      0

volatile unsigned long  lastTime = millis();
unsigned long           deltaTime = 500;  // .5 seconds

// Modes:
//  0  == Off
//  1  == Fill and Empty Strip
//  2  == Fill and Empty Ring
//  3  == Sweeper Strip
//  4  == Sweeper Strip - infinite, one set of colors
//  5  == Sweeper Ring
//  6  == Sweeper Ring - infinite, one set of colors
//  7  == Sparkle Strip
//  8  == Sparkle Ring
//  9  == Default: Flash Full
//

#define  MAX_MODES       9

volatile bool  mode_change = false;
volatile int   mode        = 0;

int last_mode = -1;

LedRing   ring;
LedStrip  strip;

/**
 * Interrupt Method
 *
 * Cycle through Modes.  Triggered by pushbutton switch.
 * Each time the switch is closed, the mode switches to
 * the next mode value.
 */
void ModeInterrupt()
{
	// Attempting to debounce button to prevent false mode changes
	unsigned long  nowTime = millis();

	if ( nowTime < ( lastTime + deltaTime ) )
	{
		// This is a bounce
		return;
	}

	lastTime = nowTime;

	// Mode Change
	if ( mode < MAX_MODES )
	{
		// Increment to next Mode.
		++mode;
	}
	else
	{
		// Reset after last Mode reached.
		mode = 0;
	}

	// Set flag to let other code that the mode has changed.
	mode_change = true;

}   // end of ModeInterrupt()

void clear_all()
{
	ring.getDevice()->clear();
	ring.getDevice()->show();

	strip.getDevice()->clear();
	strip.getDevice()->show();
}

/**
 * Turns off all LED Devices.
 *
 * Turns off by clearing all the LEDs, effectively setting them to black.
 *
 * Note, there is no need to check for mode change since this is a one shot
 * method.
 */
void  mode_off()
{
	clear_all();
	delay(1000);
}

void mode_solid( LedDevice * dLEDs )
{
	Colors     colors;
	FillSolid  solid(CRGB::White, CRGB::Black, dLEDs);

	dLEDs->setBackground( CRGB::Black );

	for ( ; ; )
	{
		solid.setForeground(colors.nextColor());
		solid.run();
		CHECK_MODE_CHANGE;
	}
}


void mode_sweeper( LedDevice * dLEDs, int nLEDs, int cycles )
{
	Colors  color;

	dLEDs->setBackground( CRGB::Black );

	Sweeper  sweep(dLEDs);

	sweep.setNumLEDs(nLEDs);
	sweep.setCycles(cycles);

	for ( ; ; )
	{
		dLEDs->setForeground( color.nextColor() );
		sweep.run();
		CHECK_MODE_CHANGE;
	}
}

void mode_iSweep(LedDevice * dLEDs, CRGB fColor, CRGB bColor, int nLEDs)
{
	dLEDs->setBackground( bColor );
	dLEDs->setForeground( fColor );

	Sweeper   sweep( dLEDs );

	sweep.setNumLEDs( nLEDs );
	sweep.setCycles(0);

	for ( ; ; )
	{
		sweep.run();
		CHECK_MODE_CHANGE;
	}
}


void mode_sparkle( LedDevice * dLEDs )
{
	SparkleLEDs  lights( dLEDs );

	lights.run();
}


void mode_default()
{
	Colors colorWheel;
	CRGB   color;
	int    maxColors = Colors::getMaxJustColors();

	for ( ; ; )
	{
		color = colorWheel.nextColor();

		ring.setLEDs(color);
		ring.show();

		strip.setLEDs(color);
		strip.show();

		CHECK_MODE_CHANGE;
		delay(1000);
		CHECK_MODE_CHANGE;
	}
}

void setup()
{
	// Initialize Serial Communication, used for debugging
	Serial.begin(9600);

	// Initialize Pseudo Random Generator.
	// Use the voltage of a floating GPIO pin that will have a unspecified
	// voltage, as the seed.
	randomSeed(analogRead(UNUSED_PIN));

	// Setup Interrupt for Mode Changes
	//
	// Using 10kOhm resister connecting INTR_PIN to ground so that the
	// Interrupt Pin is LOW when the switch is open.  When the switch
	// is closed, the Interrupt Pin goes to HIGH.  Interrupt is triggered
	// when the switch button is pushed, not when it is released.
	pinMode( INTR_PIN, INPUT);
	attachInterrupt(INTR, ModeInterrupt, RISING);

	Serial.println("Initialization Done.\r");
}

void loop()
{
	mode_change = false;

	if ( mode != last_mode )
	{
		Serial.print("New Mode: ");
		Serial.print(mode);
		Serial.print("\n\r");

		last_mode = mode;
	}

	clear_all();

	switch ( mode )
	{
		case 0:  // Off
			mode_off();
			break;

		case 1:  // Fill Solid Strip
			mode_solid( & strip );
			break;

		case 2:  // Fill Solid Ring
			mode_solid( &ring );
			break;

		case 3:  // Sweeper Strip
			mode_sweeper( &strip, 10, 4);
			// mode_sweepStrip(4);
			break;

		case 4:  // Sweeper Infinite Strip
			mode_iSweep( &strip, CRGB::Red, CRGB::DarkBlue, 10 );
			break;

		case 5:  // Sweeper Ring
			mode_sweeper( &ring, 3, 4);
			//mode_sweepRing(4);
			break;

		case 6:  // Sweeper Infinity Ring
			//mode_iSweep( &ring, CRGB::Green, CRGB::Violet, 3 );
			mode_iSweep( &ring, CRGB::Blue, CRGB::Yellow, 3 );
			break;

		case 7:  // Sparkles Strip
			mode_sparkle( &strip );
			break;

		case 8:  // Sparkles Ring
			mode_sparkle( &ring );
			break;

		default:
			mode_default();
			break;
	}

	return;
}
