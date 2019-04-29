/**
 * Abstract base class for different ways of using LED units in a LedDevice.
 *
 *  @date   Created on January 18, 2019
 *  @author Steven F. LeBrun
 */

#ifndef LIGHTSHOW_H_
#define LIGHTSHOW_H_

#include <FastLED.h>

#include "Interrupts.h"
#include "LedDevice.h"

/**
 * Macro function that determines if the Interrupt method has run
 * and forces the current method to exit.  A flag is set to true so
 * that the calling method can also determine if the Interrupt method
 * has ran.
 */
#define  CHECK_INTR  if ( mode_change ) { exitRun = true; return; }

/**
 * Macro function that forces the current method to exit if a called
 * method detected that an Interrupt has occured.
 */
#define  CHECK_EXIT  if ( exitRun ) { return; }

/**
 * Abstract Base Class that is used for running a "light show" on an
 * LED Device.  The derived classes provide the code for the actual
 * control of the LED units in the LED Device.
 */
class LightShow
{
  protected:
	/**
	 * Boolean flag used to pass along information about detected
	 * Interrupts.  Interrupts are used to exit the current light show
	 * and start a different one.
	 */
    bool exitRun     = false;

    /**
     * The pointer to the LED Device that the light show is runs on.
     * This object is created outside of this class and passed to it
     * through the constructor.
     */
    LedDevice * device;

  public:
    /**
     * Constructor.
     *
     * @param dLEDs A pointer to the LED Device that this instance works on.
     */
    LightShow( LedDevice * dLEDs );

    /**
     * Destructor.
     *
     * Note, the Destructor does not free any resources used by the LED Device
     * since the LED Device is the responsibility of another object.
     */
    virtual ~LightShow();

    /**
     * This virtual method is supplied by the derived class.  It is used to
     * perform the actual light show.  It may be a single pass method or
     * contain an infinite loop.  If it contains an infinite loop, the loop
     * should terminate when an interrupt occurs to change mode.
     */
    virtual void display( ) = 0;

    /**
     * Provides access to the interrupt state.  It is used to determine if the
     * light show should terminate so another light show can begin.
     *
     * @return Returns @b true if the light show should terminate and @b false
     *         if the light show can continue running.
     */
    bool stopNow() { return exitRun; };

    /**
     * Wrapper method for run(true).
     *
     * This method will always clear the display before starting the light show.
     */
    void run(  )
    {
      run(true);
    }

    /**
     * The method that starts the light show as defined by the virtual method display().
     *
     * @param clear  Boolean flag.  If set to @b true, the LED Device will be reset to the
     *               default background color before starting the light show.  If set to
     *               @b false, the LED device will start the light show in the same state
     *               in which it exited the previous light show.
     */
    void run( bool clear )
    {
    	// To clear or not to clear the LED Device.
    	if ( clear )
    	{
    		device->showBackground();
    	}

    	// Run the Light Show.
    	display();
    }

};   // end of abstract class lightShow


#endif /* LIGHTSHOW_H_ */
