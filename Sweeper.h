/**
 * Light Show derived class that moves a set of color values across the
 * LED Device both forward and backwards.
 *
 *  @date Created on January 24, 2019
 *  @author Steven F. LeBrun
 *  <br/><br/>
 */

#ifndef SWEEPER_H_
#define SWEEPER_H_

#include "LightShow.h"

/**
 * The Light Show derived class that sweeps a fixed number of LED Units back
 * and forth across the LED Device.  This simulates the eyes of the Cylons from
 * Battlestar Galactica and KITT on Knight Rider.
 */
class Sweeper: public LightShow
{
	private:
		/**
		 * The amount of time, in milliseconds, to display one position of
		 * the foreground LED Units before showing the next.  The greater this
		 * value is set to, the slower the cycles occurs.
		 */
		static  const int SWEEP_DELAY;

	protected:
		/**
		 * The number of Foreground Pixels [LEDs] that sweep back and forth.
		 */
		int  fPixels;

		/**
		 * Number of times to perform a sweep, both forward and backward.
		 *
		 * If nCycles to zero or negative, perform an infinite number of
		 * sweeps, exiting on Mode Change Interrupt.
		 */
		int nCycles;

	public:
		/**
		 * Constructor.
		 *
		 * NOTE, the number of LED Units to set to the foreground color and
		 * the number of cycles to perform are not set in the constructor
		 * and must be set manually before calling display().  This allows
		 * an instance of this class to be used multiple times with different
		 * foreground and background colors and different number of cycles
		 * in order to minimize the data space used on the Arduino.
		 *
		 * @param dLEDs  Pointer to the LED Device to be used.
		 */
		Sweeper( LedDevice * dLEDs );

		/**
		 * Destructor.
		 *
		 * Note, the resources of the LED Device are not released by this
		 * destructor because the LED Device object is owned and is the
		 * responsibility of another object.
		 */
		virtual ~Sweeper();

		/**
		 * The method that controls the actual Light Show.
		 *
		 * If the number of cycles is finite, this method will return after
		 * that many full cycles has occurred.  If the number of cycles is
		 * set to infinite, this method will only return after a Mode Change
		 * Interrupt has occurred.
		 *
		 * @pre A call to setNumLEDs() and to setCycles() must be made before
		 *      this method can be invoked, implicitly though the run() in the
		 *      parent class.
		 */
		virtual void display( );

		/**
		 * An inline method to allow read-only access to the number of LED Units
		 * used for the foreground color.
		 *
		 * @return  The number of LED Units set to the foreground color at any
		 *          given time.
		 */
		int getNumLEDs()
		{
			return fPixels;
		}

		/**
		 * Sets the number of LED Units that will be set to the foreground color.
		 * The rest of the LED Units will be set to the background color.
		 *
		 * @param numLEDs The number of LED Units used during the sweeep to show
		 *                the foreground color.  This should be a value less than
		 *                the number of LED Units in the LED Device.
		 */
		void setNumLEDs( int numLEDs );

		/**
		 * Sets the number of full cycles the display method will run before
		 * returning.  This can be a finite number or an infinite number.
		 *
		 * @param numberOfCycles  The number of cycles to perform.  If this value
		 *                        is zero, the number of cycles will be infinite.
		 */
		void setCycles( int numberOfCycles ) { nCycles = numberOfCycles; };

	protected:

		/**
		 * Moves the foreground LED Units from the beginning of the
		 * LED Device to the end.  This is the first half of a full cycle.
		 */
		void forwardSweep();

		/**
		 * Moves the foreground LED Units from the end of the LED Device to
		 * the beginning.  This is the second half of a full cycle.
		 */
		void backwardSweep();

		/**
		 * Runs a finite number of full cycles for the display() method.
		 */
		void limitedCycles();

		/**
		 * Runs an infinite number of cycles for the display() method.  This
		 * method will exit when a Mode Change Interrupt has been detected.
		 */
		void infiniteCycles();
};

#endif /* SWEEPER_H_ */
