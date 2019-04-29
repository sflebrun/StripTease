/**
 * Class derived from LedDevice to represent a strip of 60 WS2812B LED units that use
 * data pin 6 for communications.
 *
 *     @date    Created on January 17, 2019
 *     @author  Steven F. LeBrun
 *  <br/><br/>
 */

#ifndef LEDSTRIP_H_
#define LEDSTRIP_H_

#include "LedDevice.h"

/**
 * Defines the number of LED units in the device.
 */
#define  LedStrip_STRIP_SIZE  60

/**
 * Defines the Arduino GPIO pin used for communications
 * with the LED units.
 */
#define  LedStrip_DATA_PIN    6

/**
 * Class derived from LedDevice to represent a strip of 60 WS2812B LED units that use
 * data pin 6 for communications.
 *
 * This class is responsible for defining the array of colors for the LED units
 * and for creating the CFastLED instance used to communicate with the physical
 * LED units.
 *
 */
class LedStrip: public LedDevice
{
	private:
		/**
		 * The number of LED units in the device.  This constant is not
		 * currently being used.  It is hoped that it can replace the
		 * macro constant in the creation of the CFastLED instance.
		 */
		static const int   STRIP_SIZE;

		/**
		 * The array of colors for the device.  One element per LED unit.
		 */
		CRGB  strip[LedStrip_STRIP_SIZE];

	public:
		/**
		 * Constructor.
		 *
		 * Creates the CFastLED instance for the device and invokes the
		 * constructor of the parent class.
		 */
		LedStrip();

		/**
		 * Destuctor.
		 */
		virtual ~LedStrip();
};

#endif /* LEDSTRIP_H_ */
