/**
 * @file HSLAPixel.h
 *
 * @author kfoong
 */

 #ifndef CS221UTIL_HSLAPixel_H
 #define CS221UTIL_HSLAPixel_H

namespace cs221util {
  class HSLAPixel {
    public:

      double h;
      double s;
      double l;
      double a;

      HSLAPixel();

      HSLAPixel(double h_, double s_, double l_);

      HSLAPixel(double h_, double s_, double l_, double a_);

  };
}

#endif
