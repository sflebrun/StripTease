/*
 * Cylon Light Show.
 *
 *  @date Created on January 24, 2019
 *  @author Steven F. Lebrun
 */

#include "Interrupts.h"
#include "Sweeper.h"

const int Sweeper::SWEEP_DELAY = 50;

Sweeper::Sweeper( LedDevice * dLEDs ) :
	LightShow(dLEDs), fPixels( 2 ), nCycles(0)
{

}

Sweeper::~Sweeper()
{
}

void Sweeper::setNumLEDs( int numLEDs )
{
	fPixels = ( numLEDs < device->numberOfLEDs() ) ?
			numLEDs : (device->numberOfLEDs()/2);
}

void Sweeper::display( )
{
	int   i;
	int   maxLEDs = device->numberOfLEDs();

	// Initialize LEDs
	for ( i = 0 ; i < fPixels ; ++i )
	{
		device->setLED(i, device->getForeground() );
	}

	for ( i = fPixels ; i < maxLEDs ; ++i )
	{
		device->setLED(i, device->getBackground() );
	}

	device->show();

	CHECK_INTR;

	if ( nCycles > 0 )
	{
		limitedCycles();
	}
	else
	{
		infiniteCycles();
	}

	return;

}   // end of Sweeper::display()

void Sweeper::forwardSweep()
{
	int i;
	int iterations = device->numberOfLEDs() - fPixels;

	for ( i = 0 ; i < iterations ; ++i )
	{
		device->advanceLEDs();
		device->show();
		delay(SWEEP_DELAY);

		CHECK_INTR;
	}
}

void Sweeper::backwardSweep()
{
	int i;
	int iterations = device->numberOfLEDs() - fPixels;

	for ( i = 0 ; i < iterations ; ++i )
	{
		device->retreatLEDs();
		device->show();
		delay(50);

		CHECK_INTR;
	}
}

void Sweeper::limitedCycles()
{
	int  i;

	for ( i = 0 ; i < nCycles ; ++i )
	{
		forwardSweep();
		CHECK_EXIT;

		backwardSweep();
		CHECK_EXIT;
	}
}

void Sweeper::infiniteCycles()
{
	for ( ; ; )
	{
		forwardSweep();
		CHECK_EXIT;

		backwardSweep();
		CHECK_EXIT;
	}
}
