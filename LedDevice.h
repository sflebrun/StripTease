/**
 * The Base Class for set of Addressable RGB LEDs.
 *
 *      @date   Created on January 17, 2019
 *      @author Steven F. LeBrun
 *      <br/><br/>
 */

#ifndef LEDDEVICE_H_
#define LEDDEVICE_H_

#include "FastLED.h"

/**
 * The LedDevice base class defines the common functionality of a set of
 * addressable RGB LEDs.  This base class has only been tested with different
 * types of NeoPixel LED sets ( a.k.a. WS2812B LEDs).
 *
 * A set of addressable LEDs is a physical set of LED units.  Each LED
 * unit can be set to its own color.  An LED unit consists of multiple
 * LEDs and a controller chip.  For WS2812B or NeoPixel, the LED unit
 * contains red, green, and blue LEDs.  Some other types of LED units
 * include a fourth LED that is white.
 *
 * The reason this is a base class instead the class to define all LED sets
 * is that it appears that the template used to create the CFastLED instance
 * prefers macro constant for the Data Pin value.  This means that different
 * derived classes are needed for each specific LED set that has a different
 * value for its data pin. If this issue can be resolved, then there will be
 * no need for derived classes.
 */

class LedDevice
{
	protected:
		/**
		 * The object used by the FastLED library to represent the set of
		 * LED units.
		 *
		 * This variable needs to be initialized in the constructor of a
		 * derived class.  This allows derived classes to support NeoPixel
		 * devices and non-NeoPixel devices.  The template used to create
		 * an instance of the CFastLED class uses constants and macros to
		 * define both the type of LEDs in the device and the data pin used
		 * to communicate with the LED device.
		 */
		CFastLED  device;

		/**
		 * The number of LED units in the set.
		 */
		int       maxLEDs;

		/**
		 * The GPIO pin used to send data to the LED set.
		 */
		int       dataPin;

		/**
		 * The array of colors, one element per LED unit in the set.
		 *
		 * Note.  The array of colors is also stored in the device
		 *        variable.  This pointer provides easy access to
		 *        the array so that colors for the individual LED unit
		 *        can be set or read.
		 */
		CRGB     *leds;

		/**
		 * Default Foreground color.
		 *
		 * This is the color to use for when the LED unit is logically ON unless
		 * overridden with a specific color.
		 */
	    CRGB      foreground;

	    /**
	     * Default Background color.
	     *
	     * This is the color used for when the LED unit is logically OFF unless
	     * overridden with a specific color.
	     */
	    CRGB      background;

	public:
	    /**
	     * Constructor for the LedDevice base class.
	     *
	     * @param nLEDS  The number of LED units in the device.
	     * @param dPin   The GPIO Pin number used for the data pin to
	     *               communicate with the LED set.
	     * @param lights An array of colors, one element for each LED unit.
	     */
		LedDevice(int nLEDS, int dPin, CRGB *lights);

		/**
		 * Destructor for the LedDevice base class.
		 *
		 * This destructor does not explicitly do anything since the memory
		 * referenced by the leds array is owned by the derived class.
		 * This destructor is declared and defined so that base class pointers
		 * will invoke the derived class destructors and the destructors of
		 * the data members.
		 */
		virtual ~LedDevice();

		/**
		 * Provides access to the CFastLED instance.
		 *
		 * @return Returns a pointer to the CFastLED instance that represents
		 *         a set of LED units.
		 */
		CFastLED * getDevice()
		{
			return &device;
		}

		/**
		 * Provides access to the size of the LED set.
		 *
		 * @return Returns the number of LED units in the physical device.
		 */
		int numberOfLEDs()
		{
			return maxLEDs;
		}

		/**
		 * Provides access to the array of colors used to represent the settings
		 * of each LED unit in the set.
		 *
		 * @return  Returns a pointer to the array of LED colors.
		 */
		CRGB * getLEDs()
		{
			return leds;
		}

		/**
		 * Sets the color of a specific LED unit.
		 *
		 * @param offset The offset of the LED unit in the set.
		 *               The legal range of values is [0..numberOfLEDs())
		 * @param color  A Color as defined by the FastLED library.  The
		 *               color value does not have to be contained by the
		 *               Colors class.
		 */
	    void setLED(int offset, CRGB color)
	    {
	    	leds[offset] = color;
	    }

	    /**
	     * Sends the current state of the LED color array to the LED units.
	     *
	     * This will cause the LED units to change color as defined by the
	     * color array.
	     */
	    void show()
	    {
	    	device.show();
	    }


	    /**
	     * Move the color values of the LED units one position up the device.
	     * In other words, set leds[i] to leds[i-1].  The first LED unit will
	     * be set to background color: leds[0] = background.
	     */
	    void advanceLEDs();

	    /**
	     * Move the color values of the LED units one position down the device.
	     * In other words, set leds[i] to leds[i+1].  The last LED unit will be
	     * set to the background color: leds[maxLEDs - 1] = background.
	     */
	    void retreatLEDs();

	    /**
	     * Displays the current background colors on all the LED units in the device.
	     * This does not change the color values in the color array and the next
	     * call to this->show() will cause the LED units to revert to their previous
	     * settings.
	     */
	    void showBackground();

	    /**
	     * Displays the current foreground colors on all the LED units in the device.
	     * This does not change the color values in the color array and the next
	     * call to this->show() will cause the LED units to revert to their previous
	     * settings.
	     */
	    void showForeground();

	    /**
	     * Obtains the current background color.
	     *
	     * @return  Returns the current background color value.
	     */
	    CRGB  getBackground() { return background; };

	    /**
	     * Obtains the current foreground color.
	     *
	     * @return  Returns the current foreground color value.
	     */
	    CRGB  getForeground() { return foreground; };


	    /**
	     * Sets the default background color.  This does not affect any of the
	     * LED units.  The new background color will be applied as new calls
	     * are made to the methods that use the background color.
	     *
	     * @param color  The new default background color.
	     */
	    void setBackground( CRGB color );

	    /**
	     * Sets the default foreground color.  This does not affect any of the
	     * LED units.  The new foreground color will be applied as new calls
	     * are made to the methods that use the foreground color.
	     *
	     * @param color The new default foreground color.
	     */
	    void setForeground( CRGB color );

	    /**
	     * Set all the LED units to the same color.  To push this change to the
	     * LED units, call this->show() after calling this method.
	     *
	     * @param color  The FastLED defined color to set all the LED units to.
	     */
	    void setLEDs(CRGB color);

	    /**
	     * Set all the LED units to the default background color.
	     */
	    void setLEDsBackground();

	    /**
	     * Set all the LED units to the default foreground color.
	     */
	    void setLEDsForeground();

};

#endif /* LEDDEVICE_H_ */
