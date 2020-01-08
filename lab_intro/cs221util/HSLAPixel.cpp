/**
 * @@author: kfoong
 * date: jan 7, 2020
 * cpsc 221
 */

#include <iostream>
#include <string>
#include "HSLAPixel.h"

using namespace cs221util;

HSLAPixel::HSLAPixel() {
  h = 0;
  s = 0;
  l = 1.0;
  a = 1.0;
}

HSLAPixel::HSLAPixel(double h_, double s_, double l_) {
  h = h_;
  s = s_;
  l = l_;
  a = 1.0;
}

HSLAPixel::HSLAPixel(double h_, double s_, double l_, double a_) {
  h = h_;
  s = s_;
  l = l_;
  a = a_;
}
