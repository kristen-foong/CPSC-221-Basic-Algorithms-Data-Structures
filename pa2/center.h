#ifndef _CENTER_H_
#define _CENTER_H_

#include "cs221util/HSLAPixel.h"

using namespace cs221util;

/* A collection of centers is used to initiate the fill.
 *
 * A center consists of a location on an image, together with a color.
 */
struct center
{
    int x;
    int y;
    HSLAPixel color;

    center(int x, int y, HSLAPixel color)
    {
        this->x = x;
        this->y = y;
        this->color = color;
    }

    center()
    {
        x = 0;
        y = 0;
        color = HSLAPixel(240, 1., 0.5);
    } // default color is blue
};

#endif
