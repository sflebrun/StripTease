/*
 * Light Show that displays random colors.
 *
 *      @date Created on January 18, 2019
 *      @author Steven F. LeBrun
 */

#ifndef SPARKLELEDS_H_
#define SPARKLELEDS_H_

#include "LedDevice.h"
#include "LightShow.h"

/**
 * Light Show derived class that randomly sets the color of each LED Unit
 * on each iteration of the light show.
 *
 * @pre It is a precondition to using this class that a call to the
 *      randomSeed() method is called before an instance of this class is
 *      created.  Normally, this is done the Arduino setup() method.
 */
class SparkleLEDs: public LightShow
{
	private:
		/**
		 * The amount of time, in milliseconds, to display one set of random
		 * colors before resetting all the LED Units and showing the new set
		 * of random colors.  The greater this value is set to, the slower the
		 * sparkling occurs.
		 */
		static  const int SPARKLE_DELAY;

	public:
		/**
		 * Constructor.
		 *
		 * @param dLEDs  Pointer to the LED Device to be used.
		 */
		SparkleLEDs( LedDevice * dLEDs );

		/**
		 * Destructor.
		 *
		 * Note, the resources of the LED Device are not released by this
		 * destructor because the LED Device object is owned and is the
		 * responsibility of another object.
		 */
		virtual ~SparkleLEDs();

		/**
		 * The actual Light Show controls.  This method runs in an infinite
		 * loop only exiting when a Mode Change Interrupt has been detected.
		 *
		 * Each iteration of the loop starts with setting each LED Unit to a
		 * new random color and then showing the new values.  There is a
		 * percent value used to determine what percentage of the time the
		 * LED Unit changes color or stays the same.  This percentage is
		 * hardcoded into this method.
		 */
		virtual void display();

	private:
		/**
		 * This is the method that actually sets each LED Unit to a random
		 * color.  There is a percent factor used to determine whether each
		 * LED Unit as actually changed.  In addition to the percentage of
		 * the time that the color is not changed, there is also a probability
		 * that the new random color is the same as the previous color so that
		 * there is effectively no change.
		 *
		 * @param percent The percentage of the time that an LED Unit is to
		 *                be randomly changed.  Legal values [0..100].
		 */
		void setColors( long percent );
};

#endif /* SPARKLELEDS_H_ */
