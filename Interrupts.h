/**
 * Interrupts.h
 *
 * This header file declares variables that are shared between an interrupt
 * handler and the rest of the code.  These variables need to be declared
 * as Volatile so that changes are propagated immediately and optimization
 * does not screw things up by using cached copies.
 *
 *  Created on: Jan 17, 2019
 *      Author: Steven F. LeBrun
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/**
 * Boolean Flag that is set to true when an Interrupt has been handled.
 *
 * The Interrupt Handler is the only place where this variable is set to @b true.
 *
 * This variable is reset to @b false at the beginning of the loop() method since
 * it no longer matters if the mode has changed because the loop uses the current
 * value of @b mode @see StripeTease.cpp.
 */
extern   volatile bool  mode_change;

/**
 * The pushbutton used may bounce when pressed, resulting in multiple interrupts
 * being generated for each time the button is pushed.  This variable is used to
 * determine when the last interrupt occurred.  If it is too soon since the last
 * interrupt, the interrupt cased by bounce is ignored.
 *
 * Time unit:  milliseconds.
 */
extern   volatile unsigned long  lastTime;

/**
 * Macro function @b CHECK_MODE_CHANGE is used to exit a method as quickly as
 * practical after an interrupt has occurred.  This function is implemented as
 * a macro function instead of a regular function so that no additional code
 * is needed to test the return value from a regular function and to allow
 * this code, used multiple times, to be inserted inline.
 */

#define  CHECK_MODE_CHANGE  if ( mode_change ) { return; }


#endif /* INTERRUPTS_H_ */
