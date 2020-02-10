// File:        testgridlist.cpp
// Date:        2020-01-19 01:51
// Description: Catch test cases for GridList class

#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include <algorithm>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "block.h"
#include "gridlist.h"

using namespace cs221util;
using namespace std;

TEST_CASE("GridList::Constructor - InsertBack - 1x1", "[weight=1][part=gridlist]") {
  PNG img(2, 2);
  GridList gl(img, 2);

  REQUIRE(!gl.IsEmpty());
  REQUIRE(gl.Length() == 1);
}

TEST_CASE("GridList::Constructor - InsertBack - 2x1", "[weight=1][part=gridlist]") {
  PNG img(4, 2);
  GridList gl(img, 2);

  REQUIRE(!gl.IsEmpty());
  REQUIRE(gl.Length() == 2);
}

TEST_CASE("GridList::Constructor - InsertBack - linking", "[weight=1][part=gridlist]") {
  PNG img(3, 1);
  GridList gl(img, 1);

  GridNode* p0_f = gl.getNorthWest();
  GridNode* p1_f = p0_f->next;
  GridNode* p2_f = p1_f->next;

  GridNode* p2_b = gl.getSouthEast();
  GridNode* p1_b = p2_b->prev;
  GridNode* p0_b = p1_b->prev;

  REQUIRE(p0_f == p0_b);
  REQUIRE(p1_f == p1_b);
  REQUIRE(p2_f == p2_b);
}

TEST_CASE("GridList::Render - 1x1", "[weight=1][part=gridlist]") {
  PNG img(2, 2);
  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.25;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 1.0; p->l = 0.75;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 0.875;
  GridList gl(img, 2);

  PNG outimg = gl.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(p0->h == 0);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 270);
}

TEST_CASE("GridList::Render - 3x2", "[weight=1][part=gridlist]") {
  PNG img(3, 2);
  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.125;
  p = img.getPixel(1, 0);
  p->h = 45; p->s = 1.0; p->l = 0.25;
  p = img.getPixel(2, 0);
  p->h = 90; p->s = 1.0; p->l = 0.375;
  p = img.getPixel(0, 1);
  p->h = 135; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 180; p->s = 1.0; p->l = 0.625;
  p = img.getPixel(2, 1);
  p->h = 225; p->s = 1.0; p->l = 0.75;
  GridList gl(img, 1);

  PNG outimg = gl.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(2, 0);
  HSLAPixel* p3 = outimg.getPixel(0, 1);
  HSLAPixel* p4 = outimg.getPixel(1, 1);
  HSLAPixel* p5 = outimg.getPixel(2, 1);

  REQUIRE(p0->h == 0);
  REQUIRE(p1->h == 45);
  REQUIRE(p2->h == 90);
  REQUIRE(p3->h == 135);
  REQUIRE(p4->h == 180);
  REQUIRE(p5->h == 225);
}

TEST_CASE("GridList::CheckerN-Render - odd width", "[weight=1][part=gridlist]") {
  PNG img(3, 3);
  HSLAPixel* p;
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      p = img.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }
  GridList gl(img, 1);

  gl.CheckerN();
  PNG outimg = gl.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(2, 0);
  HSLAPixel* p3 = outimg.getPixel(0, 1);
  HSLAPixel* p4 = outimg.getPixel(1, 1);
  HSLAPixel* p5 = outimg.getPixel(2, 1);
  HSLAPixel* p6 = outimg.getPixel(0, 2);
  HSLAPixel* p7 = outimg.getPixel(1, 2);
  HSLAPixel* p8 = outimg.getPixel(2, 2);

  REQUIRE(p0->h == 90);
  REQUIRE(p0->l == 0.25);
  REQUIRE(p1->h == 270);
  REQUIRE(p1->l == 0.75);
  REQUIRE(p2->h == 90);
  REQUIRE(p2->l == 0.25);
  REQUIRE(p3->h == 270);
  REQUIRE(p3->l == 0.75);
  REQUIRE(p4->h == 90);
  REQUIRE(p4->l == 0.25);
  REQUIRE(p5->h == 270);
  REQUIRE(p5->l == 0.75);
  REQUIRE(p6->h == 90);
  REQUIRE(p6->l == 0.25);
  REQUIRE(p7->h == 270);
  REQUIRE(p7->l == 0.75);
  REQUIRE(p8->h == 90);
  REQUIRE(p8->l == 0.25);
}

TEST_CASE("GridList::CheckerN-Render - even width", "[weight=1][part=gridlist]") {
  PNG img(4, 3);
  HSLAPixel* p;
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      p = img.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }
  GridList gl(img, 1);

  gl.CheckerN();
  PNG outimg = gl.Render();
  HSLAPixel* p0  = outimg.getPixel(0, 0);
  HSLAPixel* p1  = outimg.getPixel(1, 0);
  HSLAPixel* p2  = outimg.getPixel(2, 0);
  HSLAPixel* p3  = outimg.getPixel(3, 0);
  HSLAPixel* p4  = outimg.getPixel(0, 1);
  HSLAPixel* p5  = outimg.getPixel(1, 1);
  HSLAPixel* p6  = outimg.getPixel(2, 1);
  HSLAPixel* p7  = outimg.getPixel(3, 1);
  HSLAPixel* p8  = outimg.getPixel(0, 2);
  HSLAPixel* p9  = outimg.getPixel(1, 2);
  HSLAPixel* p10 = outimg.getPixel(2, 2);
  HSLAPixel* p11 = outimg.getPixel(3, 2);

  REQUIRE(p0->h == 90);
  REQUIRE(p0->l == 0.25);
  REQUIRE(p1->h == 270);
  REQUIRE(p1->l == 0.75);
  REQUIRE(p2->h == 90);
  REQUIRE(p2->l == 0.25);
  REQUIRE(p3->h == 270);
  REQUIRE(p3->l == 0.75);
  REQUIRE(p4->h == 270);
  REQUIRE(p4->l == 0.75);
  REQUIRE(p5->h == 90);
  REQUIRE(p5->l == 0.25);
  REQUIRE(p6->h == 270);
  REQUIRE(p6->l == 0.75);
  REQUIRE(p7->h == 90);
  REQUIRE(p7->l == 0.25);
  REQUIRE(p8->h == 90);
  REQUIRE(p8->l == 0.25);
  REQUIRE(p9->h == 270);
  REQUIRE(p9->l == 0.75);
  REQUIRE(p10->h == 90);
  REQUIRE(p10->l == 0.25);
  REQUIRE(p11->h == 270);
  REQUIRE(p11->l == 0.75);
}

TEST_CASE("GridList::Sandwich_H - mismatch", "[weight=1][part=gridlist]") {
  PNG img_w(2, 1);
  HSLAPixel* pw = img_w.getPixel(0, 0);
  pw->h = 90; pw->s = 1.0; pw->l = 0.25;
  pw = img_w.getPixel(1, 0);
  pw->h = 90; pw->s = 1.0; pw->l = 0.25;

  PNG img_h(1, 2);
  HSLAPixel* ph = img_h.getPixel(0, 0);
  ph->h = 270; ph->s = 1.0; ph->l = 0.75;
  ph = img_h.getPixel(0, 1);
  ph->h = 270; ph->s = 1.0; ph->l = 0.75;

  GridList glw(img_w, 1);
  GridList glh(img_h, 1);

  glw.Sandwich_H(glh);

  REQUIRE(glw.Length() == 2);
  REQUIRE(glh.Length() == 2);
}

TEST_CASE("GridList::Sandwich_H - even width outer", "[weight=1][part=gridlist]") {
  PNG img_outer(4, 2);
  HSLAPixel* p;
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      p = img_outer.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_inner(2, 2);
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_inner.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_outer(img_outer, 1);
  GridList gl_inner(img_inner, 1);

  gl_outer.Sandwich_H(gl_inner);

  PNG outimg = gl_outer.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(2, 0);
  HSLAPixel* p3 = outimg.getPixel(3, 0);
  HSLAPixel* p4 = outimg.getPixel(4, 0);
  HSLAPixel* p5 = outimg.getPixel(5, 0);
  HSLAPixel* p6 = outimg.getPixel(0, 1);
  HSLAPixel* p7 = outimg.getPixel(1, 1);
  HSLAPixel* p8 = outimg.getPixel(2, 1);
  HSLAPixel* p9 = outimg.getPixel(3, 1);
  HSLAPixel* p10 = outimg.getPixel(4, 1);
  HSLAPixel* p11 = outimg.getPixel(5, 1);

  REQUIRE(gl_outer.Length() == 12);
  REQUIRE(gl_inner.Length() == 0);
  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 270);
  REQUIRE(p3->h == 270);
  REQUIRE(p4->h == 90);
  REQUIRE(p5->h == 90);
  REQUIRE(p6->h == 90);
  REQUIRE(p7->h == 90);
  REQUIRE(p8->h == 270);
  REQUIRE(p9->h == 270);
  REQUIRE(p10->h == 90);
  REQUIRE(p11->h == 90);
}

TEST_CASE("GridList::Sandwich_H - odd width outer", "[weight=1][part=gridlist]") {
  PNG img_outer(3, 2);
  HSLAPixel* p;
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      p = img_outer.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_inner(2, 2);
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_inner.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_outer(img_outer, 1);
  GridList gl_inner(img_inner, 1);

  gl_outer.Sandwich_H(gl_inner);

  PNG outimg = gl_outer.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(2, 0);
  HSLAPixel* p3 = outimg.getPixel(3, 0);
  HSLAPixel* p4 = outimg.getPixel(4, 0);
  HSLAPixel* p5 = outimg.getPixel(0, 1);
  HSLAPixel* p6 = outimg.getPixel(1, 1);
  HSLAPixel* p7 = outimg.getPixel(2, 1);
  HSLAPixel* p8 = outimg.getPixel(3, 1);
  HSLAPixel* p9 = outimg.getPixel(4, 1);

  REQUIRE(gl_outer.Length() == 10);
  REQUIRE(gl_inner.Length() == 0);
  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 270);
  REQUIRE(p2->h == 270);
  REQUIRE(p3->h == 90);
  REQUIRE(p4->h == 90);
  REQUIRE(p5->h == 90);
  REQUIRE(p6->h == 270);
  REQUIRE(p7->h == 270);
  REQUIRE(p8->h == 90);
  REQUIRE(p9->h == 90);
}

TEST_CASE("GridList::Sandwich_H - linking", "[weight=1][part=gridlist]") {
  PNG img_outer(4, 2);
  HSLAPixel* p;
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      p = img_outer.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_inner(2, 2);
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_inner.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_outer(img_outer, 1);
  GridList gl_inner(img_inner, 1);

  GridNode* outer_0_f = gl_outer.getNorthWest();
  GridNode* outer_1_f = outer_0_f->next;
  GridNode* outer_2_f = outer_1_f->next;
  GridNode* outer_3_f = outer_2_f->next;
  GridNode* outer_4_f = outer_3_f->next;
  GridNode* outer_5_f = outer_4_f->next;
  GridNode* outer_6_f = outer_5_f->next;
  GridNode* outer_7_f = outer_6_f->next;

  GridNode* inner_0_f = gl_inner.getNorthWest();
  GridNode* inner_1_f = inner_0_f->next;
  GridNode* inner_2_f = inner_1_f->next;
  GridNode* inner_3_f = inner_2_f->next;

  gl_outer.Sandwich_H(gl_inner);

  GridNode* sw_0_f = gl_outer.getNorthWest();
  GridNode* sw_1_f = sw_0_f->next;
  GridNode* sw_2_f = sw_1_f->next;
  GridNode* sw_3_f = sw_2_f->next;
  GridNode* sw_4_f = sw_3_f->next;
  GridNode* sw_5_f = sw_4_f->next;
  GridNode* sw_6_f = sw_5_f->next;
  GridNode* sw_7_f = sw_6_f->next;
  GridNode* sw_8_f = sw_7_f->next;
  GridNode* sw_9_f = sw_8_f->next;
  GridNode* sw_10_f = sw_9_f->next;
  GridNode* sw_11_f = sw_10_f->next;

  GridNode* sw_11_b = gl_outer.getSouthEast();
  GridNode* sw_10_b = sw_11_b->prev;
  GridNode* sw_9_b = sw_10_b->prev;
  GridNode* sw_8_b = sw_9_b->prev;
  GridNode* sw_7_b = sw_8_b->prev;
  GridNode* sw_6_b = sw_7_b->prev;
  GridNode* sw_5_b = sw_6_b->prev;
  GridNode* sw_4_b = sw_5_b->prev;
  GridNode* sw_3_b = sw_4_b->prev;
  GridNode* sw_2_b = sw_3_b->prev;
  GridNode* sw_1_b = sw_2_b->prev;
  GridNode* sw_0_b = sw_1_b->prev;

  REQUIRE(sw_0_f == outer_0_f);
  REQUIRE(sw_0_f == sw_0_b);
  REQUIRE(sw_1_f == outer_1_f);
  REQUIRE(sw_1_f == sw_1_b);
  REQUIRE(sw_2_f == inner_0_f);
  REQUIRE(sw_2_f == sw_2_b);
  REQUIRE(sw_3_f == inner_1_f);
  REQUIRE(sw_3_f == sw_3_b);
  REQUIRE(sw_4_f == outer_2_f);
  REQUIRE(sw_4_f == sw_4_b);
  REQUIRE(sw_5_f == outer_3_f);
  REQUIRE(sw_5_f == sw_5_b);
  REQUIRE(sw_6_f == outer_4_f);
  REQUIRE(sw_6_f == sw_6_b);
  REQUIRE(sw_7_f == outer_5_f);
  REQUIRE(sw_7_f == sw_7_b);
  REQUIRE(sw_8_f == inner_2_f);
  REQUIRE(sw_8_f == sw_8_b);
  REQUIRE(sw_9_f == inner_3_f);
  REQUIRE(sw_9_f == sw_9_b);
  REQUIRE(sw_10_f == outer_6_f);
  REQUIRE(sw_10_f == sw_10_b);
  REQUIRE(sw_11_f == outer_7_f);
  REQUIRE(sw_11_f == sw_11_b);
}

TEST_CASE("GridList::Sandwich_V - mismatch", "[weight=1][part=gridlist]") {
  PNG img_w(2, 1);
  HSLAPixel* pw = img_w.getPixel(0, 0);
  pw->h = 90; pw->s = 1.0; pw->l = 0.25;
  pw = img_w.getPixel(1, 0);
  pw->h = 90; pw->s = 1.0; pw->l = 0.25;

  PNG img_h(1, 2);
  HSLAPixel* ph = img_h.getPixel(0, 0);
  ph->h = 270; ph->s = 1.0; ph->l = 0.75;
  ph = img_h.getPixel(0, 1);
  ph->h = 270; ph->s = 1.0; ph->l = 0.75;

  GridList glw(img_w, 1);
  GridList glh(img_h, 1);

  glw.Sandwich_V(glh);

  REQUIRE(glw.Length() == 2);
  REQUIRE(glh.Length() == 2);
}

TEST_CASE("GridList::Sandwich_V - even height outer", "[weight=1][part=gridlist]") {
  PNG img_outer(2, 4);
  HSLAPixel* p;
  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_outer.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_inner(2, 2);
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_inner.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_outer(img_outer, 1);
  GridList gl_inner(img_inner, 1);

  gl_outer.Sandwich_V(gl_inner);

  PNG outimg = gl_outer.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);
  HSLAPixel* p4 = outimg.getPixel(0, 2);
  HSLAPixel* p5 = outimg.getPixel(1, 2);
  HSLAPixel* p6 = outimg.getPixel(0, 3);
  HSLAPixel* p7 = outimg.getPixel(1, 3);
  HSLAPixel* p8 = outimg.getPixel(0, 4);
  HSLAPixel* p9 = outimg.getPixel(1, 4);
  HSLAPixel* p10 = outimg.getPixel(0, 5);
  HSLAPixel* p11 = outimg.getPixel(1, 5);

  REQUIRE(gl_outer.Length() == 12);
  REQUIRE(gl_inner.Length() == 0);
  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 90);
  REQUIRE(p3->h == 90);
  REQUIRE(p4->h == 270);
  REQUIRE(p5->h == 270);
  REQUIRE(p6->h == 270);
  REQUIRE(p7->h == 270);
  REQUIRE(p8->h == 90);
  REQUIRE(p9->h == 90);
  REQUIRE(p10->h == 90);
  REQUIRE(p11->h == 90);
}

TEST_CASE("GridList::Sandwich_V - odd height outer", "[weight=1][part=gridlist]") {
  PNG img_outer(2, 3);
  HSLAPixel* p;
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_outer.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_inner(2, 2);
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_inner.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_outer(img_outer, 1);
  GridList gl_inner(img_inner, 1);

  gl_outer.Sandwich_V(gl_inner);

  PNG outimg = gl_outer.Render();
  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);
  HSLAPixel* p4 = outimg.getPixel(0, 2);
  HSLAPixel* p5 = outimg.getPixel(1, 2);
  HSLAPixel* p6 = outimg.getPixel(0, 3);
  HSLAPixel* p7 = outimg.getPixel(1, 3);
  HSLAPixel* p8 = outimg.getPixel(0, 4);
  HSLAPixel* p9 = outimg.getPixel(1, 4);

  REQUIRE(gl_outer.Length() == 10);
  REQUIRE(gl_inner.Length() == 0);
  REQUIRE(p0->h == 90);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 270);
  REQUIRE(p3->h == 270);
  REQUIRE(p4->h == 270);
  REQUIRE(p5->h == 270);
  REQUIRE(p6->h == 90);
  REQUIRE(p7->h == 90);
  REQUIRE(p8->h == 90);
  REQUIRE(p9->h == 90);
}

TEST_CASE("GridList::Sandwich_V - linking", "[weight=1][part=gridlist]") {
  PNG img_outer(2, 4);
  HSLAPixel* p;
  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_outer.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_inner(2, 2);
  for (int y = 0; y < 2; y++)
  {
    for (int x = 0; x < 2; x++)
    {
      p = img_inner.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_outer(img_outer, 1);
  GridList gl_inner(img_inner, 1);

  GridNode* outer_0_f = gl_outer.getNorthWest();
  GridNode* outer_1_f = outer_0_f->next;
  GridNode* outer_2_f = outer_1_f->next;
  GridNode* outer_3_f = outer_2_f->next;
  GridNode* outer_4_f = outer_3_f->next;
  GridNode* outer_5_f = outer_4_f->next;
  GridNode* outer_6_f = outer_5_f->next;
  GridNode* outer_7_f = outer_6_f->next;

  GridNode* inner_0_f = gl_inner.getNorthWest();
  GridNode* inner_1_f = inner_0_f->next;
  GridNode* inner_2_f = inner_1_f->next;
  GridNode* inner_3_f = inner_2_f->next;

  gl_outer.Sandwich_V(gl_inner);

  GridNode* sw_0_f = gl_outer.getNorthWest();
  GridNode* sw_1_f = sw_0_f->next;
  GridNode* sw_2_f = sw_1_f->next;
  GridNode* sw_3_f = sw_2_f->next;
  GridNode* sw_4_f = sw_3_f->next;
  GridNode* sw_5_f = sw_4_f->next;
  GridNode* sw_6_f = sw_5_f->next;
  GridNode* sw_7_f = sw_6_f->next;
  GridNode* sw_8_f = sw_7_f->next;
  GridNode* sw_9_f = sw_8_f->next;
  GridNode* sw_10_f = sw_9_f->next;
  GridNode* sw_11_f = sw_10_f->next;

  GridNode* sw_11_b = gl_outer.getSouthEast();
  GridNode* sw_10_b = sw_11_b->prev;
  GridNode* sw_9_b = sw_10_b->prev;
  GridNode* sw_8_b = sw_9_b->prev;
  GridNode* sw_7_b = sw_8_b->prev;
  GridNode* sw_6_b = sw_7_b->prev;
  GridNode* sw_5_b = sw_6_b->prev;
  GridNode* sw_4_b = sw_5_b->prev;
  GridNode* sw_3_b = sw_4_b->prev;
  GridNode* sw_2_b = sw_3_b->prev;
  GridNode* sw_1_b = sw_2_b->prev;
  GridNode* sw_0_b = sw_1_b->prev;

  REQUIRE(sw_0_f == outer_0_f);
  REQUIRE(sw_0_f == sw_0_b);
  REQUIRE(sw_1_f == outer_1_f);
  REQUIRE(sw_1_f == sw_1_b);
  REQUIRE(sw_2_f == outer_2_f);
  REQUIRE(sw_2_f == sw_2_b);
  REQUIRE(sw_3_f == outer_3_f);
  REQUIRE(sw_3_f == sw_3_b);
  REQUIRE(sw_4_f == inner_0_f);
  REQUIRE(sw_4_f == sw_4_b);
  REQUIRE(sw_5_f == inner_1_f);
  REQUIRE(sw_5_f == sw_5_b);
  REQUIRE(sw_6_f == inner_2_f);
  REQUIRE(sw_6_f == sw_6_b);
  REQUIRE(sw_7_f == inner_3_f);
  REQUIRE(sw_7_f == sw_7_b);
  REQUIRE(sw_8_f == outer_4_f);
  REQUIRE(sw_8_f == sw_8_b);
  REQUIRE(sw_9_f == outer_5_f);
  REQUIRE(sw_9_f == sw_9_b);
  REQUIRE(sw_10_f == outer_6_f);
  REQUIRE(sw_10_f == sw_10_b);
  REQUIRE(sw_11_f == outer_7_f);
  REQUIRE(sw_11_f == sw_11_b);
}

TEST_CASE("GridList::CheckerSwap - mismatch", "[weight=1][part=gridlist]") {
  PNG img_w(2, 1);
  HSLAPixel* pw = img_w.getPixel(0, 0);
  pw->h = 90; pw->s = 1.0; pw->l = 0.25;
  pw = img_w.getPixel(1, 0);
  pw->h = 90; pw->s = 1.0; pw->l = 0.25;

  PNG img_h(1, 2);
  HSLAPixel* ph = img_h.getPixel(0, 0);
  ph->h = 270; ph->s = 1.0; ph->l = 0.75;
  ph = img_h.getPixel(0, 1);
  ph->h = 270; ph->s = 1.0; ph->l = 0.75;

  GridList glw(img_w, 1);
  GridList glh(img_h, 1);

  glw.CheckerSwap(glh);

  REQUIRE(glw.Length() == 2);
  REQUIRE(glh.Length() == 2);
}

TEST_CASE("GridList::CheckerSwap - even width", "[weight=1][part=gridlist]") {
  PNG img_90(4, 3);
  HSLAPixel* p;
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      p = img_90.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_270(4, 3);
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      p = img_270.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_90(img_90, 1);
  GridList gl_270(img_270, 1);

  gl_90.CheckerSwap(gl_270);

  PNG png_90 = gl_90.Render();
  HSLAPixel* p1_0 = png_90.getPixel(0, 0);
  HSLAPixel* p1_1 = png_90.getPixel(1, 0);
  HSLAPixel* p1_2 = png_90.getPixel(2, 0);
  HSLAPixel* p1_3 = png_90.getPixel(3, 0);
  HSLAPixel* p1_4 = png_90.getPixel(0, 1);
  HSLAPixel* p1_5 = png_90.getPixel(1, 1);
  HSLAPixel* p1_6 = png_90.getPixel(2, 1);
  HSLAPixel* p1_7 = png_90.getPixel(3, 1);
  HSLAPixel* p1_8 = png_90.getPixel(0, 2);
  HSLAPixel* p1_9 = png_90.getPixel(1, 2);
  HSLAPixel* p1_10 = png_90.getPixel(2, 2);
  HSLAPixel* p1_11 = png_90.getPixel(3, 2);

  PNG png_270 = gl_270.Render();
  HSLAPixel* p2_0 = png_270.getPixel(0, 0);
  HSLAPixel* p2_1 = png_270.getPixel(1, 0);
  HSLAPixel* p2_2 = png_270.getPixel(2, 0);
  HSLAPixel* p2_3 = png_270.getPixel(3, 0);
  HSLAPixel* p2_4 = png_270.getPixel(0, 1);
  HSLAPixel* p2_5 = png_270.getPixel(1, 1);
  HSLAPixel* p2_6 = png_270.getPixel(2, 1);
  HSLAPixel* p2_7 = png_270.getPixel(3, 1);
  HSLAPixel* p2_8 = png_270.getPixel(0, 2);
  HSLAPixel* p2_9 = png_270.getPixel(1, 2);
  HSLAPixel* p2_10 = png_270.getPixel(2, 2);
  HSLAPixel* p2_11 = png_270.getPixel(3, 2);

  REQUIRE(gl_90.Length() == 12);
  REQUIRE(gl_270.Length() == 12);
  REQUIRE(p1_0->h == 90);
  REQUIRE(p1_1->h == 270);
  REQUIRE(p1_2->h == 90);
  REQUIRE(p1_3->h == 270);
  REQUIRE(p1_4->h == 270);
  REQUIRE(p1_5->h == 90);
  REQUIRE(p1_6->h == 270);
  REQUIRE(p1_7->h == 90);
  REQUIRE(p1_8->h == 90);
  REQUIRE(p1_9->h == 270);
  REQUIRE(p1_10->h == 90);
  REQUIRE(p1_11->h == 270);

  REQUIRE(p2_0->h == 270);
  REQUIRE(p2_1->h == 90);
  REQUIRE(p2_2->h == 270);
  REQUIRE(p2_3->h == 90);
  REQUIRE(p2_4->h == 90);
  REQUIRE(p2_5->h == 270);
  REQUIRE(p2_6->h == 90);
  REQUIRE(p2_7->h == 270);
  REQUIRE(p2_8->h == 270);
  REQUIRE(p2_9->h == 90);
  REQUIRE(p2_10->h == 270);
  REQUIRE(p2_11->h == 90);
}

TEST_CASE("GridList::CheckerSwap - odd width", "[weight=1][part=gridlist]") {
  PNG img_90(3, 3);
  HSLAPixel* p;
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      p = img_90.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_270(3, 3);
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      p = img_270.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_90(img_90, 1);
  GridList gl_270(img_270, 1);

  gl_90.CheckerSwap(gl_270);

  PNG png_90 = gl_90.Render();
  HSLAPixel* p1_0 = png_90.getPixel(0, 0);
  HSLAPixel* p1_1 = png_90.getPixel(1, 0);
  HSLAPixel* p1_2 = png_90.getPixel(2, 0);
  HSLAPixel* p1_3 = png_90.getPixel(0, 1);
  HSLAPixel* p1_4 = png_90.getPixel(1, 1);
  HSLAPixel* p1_5 = png_90.getPixel(2, 1);
  HSLAPixel* p1_6 = png_90.getPixel(0, 2);
  HSLAPixel* p1_7 = png_90.getPixel(1, 2);
  HSLAPixel* p1_8 = png_90.getPixel(2, 2);

  PNG png_270 = gl_270.Render();
  HSLAPixel* p2_0 = png_270.getPixel(0, 0);
  HSLAPixel* p2_1 = png_270.getPixel(1, 0);
  HSLAPixel* p2_2 = png_270.getPixel(2, 0);
  HSLAPixel* p2_3 = png_270.getPixel(0, 1);
  HSLAPixel* p2_4 = png_270.getPixel(1, 1);
  HSLAPixel* p2_5 = png_270.getPixel(2, 1);
  HSLAPixel* p2_6 = png_270.getPixel(0, 2);
  HSLAPixel* p2_7 = png_270.getPixel(1, 2);
  HSLAPixel* p2_8 = png_270.getPixel(2, 2);

  REQUIRE(gl_90.Length() == 9);
  REQUIRE(gl_270.Length() == 9);
  REQUIRE(p1_0->h == 90);
  REQUIRE(p1_1->h == 270);
  REQUIRE(p1_2->h == 90);
  REQUIRE(p1_3->h == 270);
  REQUIRE(p1_4->h == 90);
  REQUIRE(p1_5->h == 270);
  REQUIRE(p1_6->h == 90);
  REQUIRE(p1_7->h == 270);
  REQUIRE(p1_8->h == 90);

  REQUIRE(p2_0->h == 270);
  REQUIRE(p2_1->h == 90);
  REQUIRE(p2_2->h == 270);
  REQUIRE(p2_3->h == 90);
  REQUIRE(p2_4->h == 270);
  REQUIRE(p2_5->h == 90);
  REQUIRE(p2_6->h == 270);
  REQUIRE(p2_7->h == 90);
  REQUIRE(p2_8->h == 270);
}

TEST_CASE("GridList::CheckerSwap - linking", "[weight=1][part=gridlist]") {
  PNG img_90(3, 3);
  HSLAPixel* p;
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      p = img_90.getPixel(x, y);
      p->h = 90; p->s = 1.0; p->l = 0.25;
    }
  }

  PNG img_270(3, 3);
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      p = img_270.getPixel(x, y);
      p->h = 270; p->s = 1.0; p->l = 0.75;
    }
  }

  GridList gl_90(img_90, 1);
  GridList gl_270(img_270, 1);

  GridNode* p90_0_f = gl_90.getNorthWest();
  GridNode* p90_1_f = p90_0_f->next;
  GridNode* p90_2_f = p90_1_f->next;
  GridNode* p90_3_f = p90_2_f->next;
  GridNode* p90_4_f = p90_3_f->next;
  GridNode* p90_5_f = p90_4_f->next;
  GridNode* p90_6_f = p90_5_f->next;
  GridNode* p90_7_f = p90_6_f->next;
  GridNode* p90_8_f = p90_7_f->next;

  GridNode* p270_0_f = gl_270.getNorthWest();
  GridNode* p270_1_f = p270_0_f->next;
  GridNode* p270_2_f = p270_1_f->next;
  GridNode* p270_3_f = p270_2_f->next;
  GridNode* p270_4_f = p270_3_f->next;
  GridNode* p270_5_f = p270_4_f->next;
  GridNode* p270_6_f = p270_5_f->next;
  GridNode* p270_7_f = p270_6_f->next;
  GridNode* p270_8_f = p270_7_f->next;

  gl_90.CheckerSwap(gl_270);

  GridNode* s90_0_f = gl_90.getNorthWest();
  GridNode* s90_1_f = s90_0_f->next;
  GridNode* s90_2_f = s90_1_f->next;
  GridNode* s90_3_f = s90_2_f->next;
  GridNode* s90_4_f = s90_3_f->next;
  GridNode* s90_5_f = s90_4_f->next;
  GridNode* s90_6_f = s90_5_f->next;
  GridNode* s90_7_f = s90_6_f->next;
  GridNode* s90_8_f = s90_7_f->next;

  GridNode* s90_8_b = gl_90.getSouthEast();
  GridNode* s90_7_b = s90_8_b->prev;
  GridNode* s90_6_b = s90_7_b->prev;
  GridNode* s90_5_b = s90_6_b->prev;
  GridNode* s90_4_b = s90_5_b->prev;
  GridNode* s90_3_b = s90_4_b->prev;
  GridNode* s90_2_b = s90_3_b->prev;
  GridNode* s90_1_b = s90_2_b->prev;
  GridNode* s90_0_b = s90_1_b->prev;

  GridNode* s270_0_f = gl_270.getNorthWest();
  GridNode* s270_1_f = s270_0_f->next;
  GridNode* s270_2_f = s270_1_f->next;
  GridNode* s270_3_f = s270_2_f->next;
  GridNode* s270_4_f = s270_3_f->next;
  GridNode* s270_5_f = s270_4_f->next;
  GridNode* s270_6_f = s270_5_f->next;
  GridNode* s270_7_f = s270_6_f->next;
  GridNode* s270_8_f = s270_7_f->next;

  GridNode* s270_8_b = gl_270.getSouthEast();
  GridNode* s270_7_b = s270_8_b->prev;
  GridNode* s270_6_b = s270_7_b->prev;
  GridNode* s270_5_b = s270_6_b->prev;
  GridNode* s270_4_b = s270_5_b->prev;
  GridNode* s270_3_b = s270_4_b->prev;
  GridNode* s270_2_b = s270_3_b->prev;
  GridNode* s270_1_b = s270_2_b->prev;
  GridNode* s270_0_b = s270_1_b->prev;

  REQUIRE(s90_0_f == p90_0_f);
  REQUIRE(s90_0_f == s90_0_b);
  REQUIRE(s90_1_f == p270_1_f);
  REQUIRE(s90_1_f == s90_1_b);
  REQUIRE(s90_2_f == p90_2_f);
  REQUIRE(s90_2_f == s90_2_b);
  REQUIRE(s90_3_f == p270_3_f);
  REQUIRE(s90_3_f == s90_3_b);
  REQUIRE(s90_4_f == p90_4_f);
  REQUIRE(s90_4_f == s90_4_b);
  REQUIRE(s90_5_f == p270_5_f);
  REQUIRE(s90_5_f == s90_5_b);
  REQUIRE(s90_6_f == p90_6_f);
  REQUIRE(s90_6_f == s90_6_b);
  REQUIRE(s90_7_f == p270_7_f);
  REQUIRE(s90_7_f == s90_7_b);
  REQUIRE(s90_8_f == p90_8_f);
  REQUIRE(s90_8_f == s90_8_b);

  REQUIRE(s270_0_f == p270_0_f);
  REQUIRE(s270_0_f == s270_0_b);
  REQUIRE(s270_1_f == p90_1_f);
  REQUIRE(s270_1_f == s270_1_b);
  REQUIRE(s270_2_f == p270_2_f);
  REQUIRE(s270_2_f == s270_2_b);
  REQUIRE(s270_3_f == p90_3_f);
  REQUIRE(s270_3_f == s270_3_b);
  REQUIRE(s270_4_f == p270_4_f);
  REQUIRE(s270_4_f == s270_4_b);
  REQUIRE(s270_5_f == p90_5_f);
  REQUIRE(s270_5_f == s270_5_b);
  REQUIRE(s270_6_f == p270_6_f);
  REQUIRE(s270_6_f == s270_6_b);
  REQUIRE(s270_7_f == p90_7_f);
  REQUIRE(s270_7_f == s270_7_b);
  REQUIRE(s270_8_f == p270_8_f);
  REQUIRE(s270_8_f == s270_8_b);
}
