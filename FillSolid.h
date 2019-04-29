/*
 * Light Show derived class that first fills the LED Device with the
 * foreground color and then with the background color.
 *
 *      @date Created on January 19, 2019
 *      @author Steven F. LeBrun
 *      <br/><br/>
 */

#ifndef FILLSOLID_H_
#define FILLSOLID_H_

#include "FillAndClear.h"

/**
 * Light Show class that fills the LED Device, one LED Unit at a time.
 * Filling the first LED Unit with the foreground color, showing the
 * new settings and then advancing the color of the LED Units before
 * repeating.  Once all the LED Units are set to the foreground color,
 * the Light Show starts setting the first LED Unit to the background
 * color, advancing the color values and repeating until all the
 * LED Units are showing the default background color.
 */
class FillSolid: public FillAndClear
{
	private:
		/**
		 * The default foreground color to use.
		 */
		CRGB  foreground;

		/**
		 * The default background color to use.
		 */
		CRGB  background;

	public:
		/**
		 * Constructor.  Initializes this derived class and its parent classes.
		 *
		 * @param fColor The foreground color to use.
		 * @param bColor The background color to use.
		 * @param dLED   Pointer to the LED Device to use.
		 */
		FillSolid( CRGB fColor, CRGB bColor, LedDevice * dLED );

		/**
		 * Destructor.
		 *
		 * Note, the resources of the LED Device are not released by this
		 * destructor because the LED Device object is owned and is the
		 * responsibility of another object.
		 */
		virtual ~FillSolid();

		/**
		 * Provides the next color to set the first LED Unit to each time
		 * the color values are moved to the next LED Unit.
		 *
		 * @param led  The number of times that this method has been invoked.
		 *             The legal range is [0 .. 2*maxLEDs)
		 *
		 * @return Returns the foreground color for the first maxLEDs calls
		 *         and the background color for the next maxLEDs calls where
		 *         maxLEDs is the number of LED Units in the LED Device.
		 */
		virtual  CRGB nextColor( int led );

		/**
		 * Changes the default foreground color after this object has been
		 * created.  Calling this method does not change any LED Unit color
		 * values.
		 *
		 * This method is provided so that the same instance of this class
		 * can be used in different light shows where the foreground and
		 * background colors are different.  This is to minimize the amount
		 * of data memory used on the Arduino.
		 *
		 * @param fColor The new foreground color to use.
		 */
		void setForeground(CRGB fColor);

		/**
		 * Changes the default background color after this object has been
		 * created.  Calling this method does not change any LED Unit color
		 * values.
		 *
		 * This method is provided so that the same instance of this class
		 * can be used in different light shows where the foreground and
		 * background colors are different.  This is to minimize the amount
		 * of data memory used on the Arduino.
		 *
		 * @param bColor The new background color to use.
		 */
		void setBackground(CRGB bColor);
};

#endif /* FILLSOLID_H_ */
