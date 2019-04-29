/**
 * XClass derived from LedDevice to represent a ring of 12 WS2812B LED units that use
 * data pin 5 for communications.
 *
 * This class is responsible for defining the array of colors for the LED units
 * and for creating the CFastLED instance used to communicate with the physical
 * LED units.
 *
 *  @date   Created on January 17, 2019
 *  @author Steven F. LeBrun
 *  <br/><br/>
 */

#ifndef LEDRING_H_
#define LEDRING_H_

#include <FastLED.h>

#include "LedDevice.h"

/**
 * Defines the number of LED units in the device.
 */
#define  LedRing_RING_SIZE  12

/**
 * Defines the Arduino GPIO pin used for communications
 * with the LED units.
 */
#define  LedRing_DATA_PIN    5

/**
 * Class derived from LedDevice to represent a ring of 12 WS2812B LED units that use
 * data pin 5 for communications.
 *
 * This class is responsible for defining the array of colors for the LED units
 * and for creating the CFastLED instance used to communicate with the physical
 * LED units.
 */

class LedRing: public LedDevice
{
	private:
		/**
		 * The number of LED units in the device.  This constant is not
		 * currently being used.  It is hoped that it can replace the
		 * macro constant in the creation of the CFastLED instance.
		 */
		static const int   RING_SIZE;

		/**
		 * The array of colors for the device.  One element per LED unit.
		 */
		CRGB  ring[LedRing_RING_SIZE];

	public:
		/**
		 * Constructor.
		 *
		 * Creates the CFastLED instance for the device and invokes the
		 * constructor of the parent class.
		 */
		LedRing();

		/**
		 * Destuctor.
		 */
		virtual ~LedRing();
};

#endif /* LEDRING_H_ */
