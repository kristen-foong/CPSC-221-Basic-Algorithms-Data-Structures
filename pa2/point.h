#ifndef _POINT_H_
#define _POINT_H_

#include "center.h"

/* Every point in the fill is associated with a location on the image,
 * and with a center. The center information is instantiated during the
 * fill. This is necessary because we need to pass center color information
 * to the color picker.
 */

struct point
{
    unsigned int x;
    unsigned int y;

    center c;

    point()
    {
        c = center();
        x = 0;
        y = 0;
    }

    point(center ctr)
    {
        c = ctr;
        x = ctr.x;
        y = ctr.y;
    }

    point(int newx, int newy, center ctr)
    {
        c = ctr;
        x = newx;
        y = newy;
    }
};

#endif
