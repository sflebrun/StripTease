/*
 * FillAndClear.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Steven F. LeBrun
 */

#include "FillAndClear.h"

FillAndClear::FillAndClear(LedDevice * dLED) :
	LightShow(dLED)
{
	maxLEDs = device->numberOfLEDs();
}

FillAndClear::~FillAndClear()
{
}

void FillAndClear::display()
 {
 	Colors  colors;

   //Serial.print("Entering FillAndClear::display()\n");
   exitRun = false;

   int i;
   int max = 2*maxLEDs;

   for ( i = 0 ; i < max ; ++i )
   {
     device->advanceLEDs();

     device->setLED(0, nextColor(i));

     device->show();
     delay(50);

     CHECK_INTR;
   }
 }
