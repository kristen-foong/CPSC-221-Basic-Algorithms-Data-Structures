/**
 * @file fadeColorPicker.h
 * Definition of a fade color picker.
 *
 */
#ifndef _FADECOLORPICKER_H_
#define _FADECOLORPICKER_H_

#include <cmath>

#include "cs221util/HSLAPixel.h"

#include "center.h"
#include "colorPicker.h"
#include "point.h"

using namespace std;

/**
 * fadeColorPicker: a functor that determines the color that should be used
 * given a point containing both an n x and a y coordinate, and the
 * coordinates and color of the center to which (x,y) has been assigned.
 * The hue and saturation of the color of (x,y)
 * is the same as the center, but the luminiance is computed as
 * newL = (oldL * fadeFactor ^ (distSq)), where oldL is the center's
 * luminance, fadeFactor is a parameter, and distSq is the squared
 * Euclidean distance between the current point and the center.
 *
 */
class fadeColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new fadeColorPicker.
     *
     * @param double fadeFactor   The decay factor.
     */
    fadeColorPicker(double fadeFactor);

    /**
     * Picks the color for pixel (x, y), which is a member of point p.
     * The new color consists of components h, s, and l.
     * The hue h, and saturation s, are unchanged by
     * the function, but the luminance decays as the
     * distance from the current point to the center,
     * increases.
     *
     *  The new luminance is simply newL = centerL * (fadeFactor)^(distSq).
     *  centerL, and all the information you need to compute distSq is
     * given via the input parameter p.
     *
     * @param p   The point for which you're picking a color
     * @return    The color chosen for (p).
     */
    virtual HSLAPixel operator()(point p);

  private:
    double fadeFactor;
};

#endif
