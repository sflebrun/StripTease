/**
 * The Colors class is used to encapsulate the colors constants provided by
 * the FastLED library.
 *
 * It serves two purposes.  One is to define subset of Colors that I deemed
 * useful.  The criteria for colors in this subset is that they appear different
 * from each other colors in the subset.  There are groups of colors that look too
 * similar even though they have different numerical values.
 *
 * @see Colors::allColors on instructions for adding or changing the colors in
 *      the subset.
 *
 * Most of the methods are static methods, allowing access to the colors without
 * having to create an object of this class.  This allows data inside the class to
 * be defined only once, saving data space on the Arduino.
 *
 * The exception to this is the method nextColor().  It uses an internal variable
 * to keep track of what was the last color returned.  To use the nextColor()
 * method, an instance of the class must be created.  The instance does not
 * duplicate the static data, thus minimizing the footprint of the class.
 *
 *  @date   Created on January 18, 2019
 *  @author Steven F. LeBrun
 *  <br/><br/>
 */

#ifndef COLORS_H_
#define COLORS_H_

#include <FastLED.h>


class Colors
{
	private:
		/**
		 * The array that contains all the colors in the subset.
		 *
		 * The first color must be Black and the second one must be white.
		 * This allows access to all colors except black and to all colors
		 * except for black and white.
		 *
		 * New colors can be added to the subset simply by adding them to
		 * the definition of the allColors array in the Colors.cpp file.
		 * The code will automatically determine the new length of the array
		 * at compile time.
		 *
		 * Colors can be removed, added and rearranged in the array so long
		 * as Black and White remain the first and second elements in the array.
		 */
		static const   CRGB  allColors[];

		/**
		 * The pointer to the array of Colors starting with the color White.
		 */
		static CRGB  * noBlack    = allColors + 1;

		/**
		 * The pointer to the array of Colors starting with the first color
		 * after Black and White.
		 */
		static CRGB  * justColors = allColors + 2;

		/**
		 * The number of elements in the allColors array.
		 */
		static const   int MAX_ALL_COLORS;

		/**
		 * The number of elements in the allColor array, ignoring Black.
		 */
		static const   int MAX_NO_BLACK;

		/**
		 * The number of colors in the allColor array that are not Black and White.
		 */
		static const   int MAX_JUST_COLORS;

		/**
		 * cnt == The offset of the current color.  This is used in instances of the
		 * Color class, thus allowing multiple instances to access the colors in their
		 * own order.
		 *
		 * Used to get the next color from the array justColors.  Initial
		 * value is set to the last color because variable is used mainly
		 * to get the next color.  Setting it to the last color will result
		 * in the first color returned by nextColor() will be the first one.
		 *
		 * Legal Range = [0..MAX_JUST_COLORS);
		 */
		int  cnt = MAX_JUST_COLORS -1;

	public:
		/**
		 * Constructor.  Creates and initializes a non-static instance of this class.
		 */
		Colors();

		/**
		 * Destructor.   No dynamic resources used by this class so there really is
		 * nothing for the destructor to do except normal, defaul cleanup.
		 */
		virtual ~Colors();

		/**
		 * Selects one of the colors from the subset defined by the static part of
		 * this class.
		 *
		 * @return  Returns a randomly selected color.  Black and White are not included
		 *          in the set of colors selected from.
		 */
		static CRGB  randomJustColor();

		/**
		 * Selects one of the colors from the subset defined by the static part of
		 * this class.
		 *
		 * @return  Returns a randomly selected color.  Black and White are included
		 *          in the set of colors selected from.
		 */
		static CRGB  randomAllColor();

		/**
		 * Selects one of the colors from the subset defined by the static part of
		 * this class.
		 *
		 * @return  Returns a randomly selected color.  Black is not included
		 *          in the set of colors selected from, though White is included.
		 */
		static CRGB  randomNoBlack();

		/**
		 * Exposes the number of non black and white colors are in the set of colors.
		 *
		 * @return  Returns the number of colors in the set that are not Black or White.
		 */
		static int   getMaxJustColors()
		{ return MAX_JUST_COLORS; };

		/**
		 * Obtains a color from the subset.
		 *
		 * @param offset The offset of the Color in the set.  Legal range is [0..MaxJustColors).
		 *
		 * @pre It is the responsibility of the caller to insure that the value of @b offset is
		 *      within the legal range.
		 *
		 * @return Returns the selected color.  Note, Black and White are not accessible with
		 *         this method.
		 */
		static CRGB  getJustColor( int offset )
		{ return allColors[offset + 2]; };

		/**
		 * Non-Static method used to obtain the next color in the set.
		 *
		 * This method loops through the Just Color subset and returns the next color in the
		 * set.  This method automatically returns the first color when the previous call
		 * returns the last color.
		 *
		 * @return  Returns the next color available in the set of Just Colors, no Black or White.
		 *          The order of colors returned is defined by the order in which they are stored.
		 */
		CRGB   nextColor();
};

#endif /* COLORS_H_ */
