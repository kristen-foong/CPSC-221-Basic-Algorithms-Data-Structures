/**
 * @file colorPicker.h
 *
 * Definition of a color picker abstract base class.
 *
 */
#ifndef _COLORPICKER_H_
#define _COLORPICKER_H_

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"

#include "point.h"

using namespace cs221util;

/**
 * colorPicker: a functor that determines the color that should be used
 * given an x and y coordinate.
 *
 */
class colorPicker
{
  public:
    /**
     * Destructor: does nothing, but as it is virtual, you may overload it in
     * derived classes if needed.
     */
    virtual ~colorPicker(){};

    /**
     * Picks the color for pixel (x, y).
     *
     * This function **must** be defined in the subclass! It chooses a color for
     * the given point and returns it.
     *
     * For example, the gridColorPicker::operator()() function is defined so as
     * to return a color if x or y is divisible by the grid spacing, and white
     * otherwise. In this way, if you colored each pixel in an image whatever
     * color the gridColorPicker chose, you would end up with a grid.
     *
     * For the other patterns, you will have to figure out how to "pick" the
     * colors.
     *
     * @param p   The point for which you're picking a color.
     * @return    The color chosen for (p).
     */
    virtual HSLAPixel operator()(point p) = 0;
};

#endif
