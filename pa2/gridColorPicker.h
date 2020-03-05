/**
 * @file gridColorPicker.h
 * Definition of a grid color picker.
 *
 */
#ifndef GRIDCOLORPICKER_H
#define GRIDCOLORPICKER_H

#include "colorPicker.h"
#include "point.h"

/**
 * gridColorPicker: a functor that determines the color that should be used
 * given a point using a grid pattern.
 *
 */
class gridColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new gridColorPicker.
     *
     * @param fillColor     Color for the border between cells of the grid.
     * @param gridSpacing   Spacing between cells of the grid.
     */
    gridColorPicker(HSLAPixel fillColor, int gridSpacing);

    /**
     * Picks the color for pixel (x, y). If the x or y coordinate is a
     * multiple of the spacing, it will be filled with the fillColor.
     * otherwise, it will be filled with white.
     *
     * @param p   The point for which you're picking a color
     * @return    The color chosen for (p).
     */
    virtual HSLAPixel operator()(point p);

  private:
    HSLAPixel color; // Color used for the grid border.
    int spacing;     // Spacing for cells in the grid.
};

#endif
