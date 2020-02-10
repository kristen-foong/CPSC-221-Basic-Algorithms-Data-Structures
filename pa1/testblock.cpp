// File:        testblock.cpp
// Date:        2020-01-18 23:52
// Description: Catch test cases for Block class

#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include <algorithm>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "block.h"

using namespace cs221util;
using namespace std;

TEST_CASE("Block::Build-Dimension full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 0.5;
  
  Block b;
  b.Build(img, 0, 0, 2);

  REQUIRE(b.Dimension() == 2);
}

TEST_CASE("Block::Build-Dimension partial PNG", "[weight=1][part=block]") {

  PNG img(4, 4);

  HSLAPixel* p;
  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
    {
      p = img.getPixel(x, y);
      p->h = (double) 90 * max(x, y); p->s = 1.0; p->l = 0.5;
    }
  }

  Block b;
  b.Build(img, 2, 2, 2);

  REQUIRE(b.Dimension() == 2);
}

TEST_CASE("Block::Build-Render full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 0.5;

  Block b;
  b.Build(img, 0, 0, 2);

  PNG outimg(2, 2);
  b.Render(outimg, 0, 0);

  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(b.Dimension() == 2);
  REQUIRE(p0->h == 0);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 270);
}

TEST_CASE("Block::Build-Render partial PNG", "[weight=1][part=block]") {

  PNG img(4, 4);

  HSLAPixel* p;
  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
    {
      p = img.getPixel(x, y);
      p->h = (double)90 * max(x, y); p->s = 1.0; p->l = 0.5;
    }
  }

  Block b;
  b.Build(img, 1, 0, 2);

  PNG outimg(4, 4);
  b.Render(outimg, 0, 0);
  b.Render(outimg, 2, 0);
  b.Render(outimg, 0, 2);
  b.Render(outimg, 2, 2);

  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(b.Dimension() == 2);
  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 180);

  p0 = outimg.getPixel(2, 0);
  p1 = outimg.getPixel(3, 0);
  p2 = outimg.getPixel(2, 1);
  p3 = outimg.getPixel(3, 1);

  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 180);

  p0 = outimg.getPixel(0, 2);
  p1 = outimg.getPixel(1, 2);
  p2 = outimg.getPixel(0, 3);
  p3 = outimg.getPixel(1, 3);

  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 180);

  p0 = outimg.getPixel(2, 2);
  p1 = outimg.getPixel(3, 2);
  p2 = outimg.getPixel(2, 3);
  p3 = outimg.getPixel(3, 3);

  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 180);
}

TEST_CASE("Block::Build-Negative full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.125;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.25;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 0.75;

  Block b;
  b.Build(img, 0, 0, 2);
  b.Negative();

  PNG outimg(2, 2);
  b.Render(outimg, 0, 0);

  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(p0->h == 180);
  REQUIRE(p0->l == 0.875);
  REQUIRE(p1->h == 270);
  REQUIRE(p1->l == 0.75);
  REQUIRE(p2->h == 0);
  REQUIRE(p2->l == 0.5);
  REQUIRE(p3->h == 90);
  REQUIRE(p3->l == 0.25);
}