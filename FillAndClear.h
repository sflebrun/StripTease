/**
 * Base class for Light Shows that turn all LED units in the LED Device.
 *
 * @date Created on  January 19, 2019
 * @author Steven F. LeBrun
 */

#ifndef FILLANDCLEAR_H_
#define FILLANDCLEAR_H_

#include <FastLED.h>

#include "Colors.h"
#include "Interrupts.h"
#include "LightShow.h"

/**
 * Abstract base class for light shows that fill in the LED Device, one LED Unit
 * at a time then continues to clear them, one LED Unit at a time.
 */
class  FillAndClear : public LightShow
{
	protected:
		/**
		 * The number of LED Units in the LED Device.  This value is obtained
		 * from the LED Device object and is used as a fast way to access the
		 * value so that methods do not need to be called each time.
		 */
		int  maxLEDs;

    public:
		/**
		 * Constructor.
		 *
		 * @param dLED  Pointer to the LED Device to be operated on by this
		 *              object.  The LED Device address is passed to the
		 *              parent class of this class.
		 */
		FillAndClear(LedDevice * dLED);

		/**
		 * Destructor
		 *
		 * Note, the resources of the LED Device are not released by this
		 * destructor because the LED Device object is owned and is the
		 * responsibility of another object.
		 */
		virtual ~FillAndClear();

		/**
		 * The virtual method that determines what the next color to applied
		 * to the first LED Unit each iterations when the values for each
		 * LED unit is moved to the next LED Unit in the chain.  In other words,
		 * this is the next color to be applied to the LED Device.
		 *
		 * @param led The number of times this method has been invoked.  The
		 *        range is from zero to twice the number of LED Units in the
		 *        LED Device.  It is assumed that the values of 0 to (maxLEDs -1)
		 *        represents the filling stage of the light show and from
		 *        maxLED to (2*maxLEDs - 1) is the clearing stage, though
		 *        the derived class can do whatever it wants during both
		 *        stages.
		 * @return
		 */
		virtual CRGB nextColor( int led) = 0;

		/**
		 * The method that contains the code for the actual light show.  It will
		 * advance the LED Unit color values and set the first LED Unit to the
		 * color provided by the virtual method nextColor().
		 */
		virtual void display();

 };   // end of class fillAndClear


#endif /* FILLANDCLEAR_H_ */
