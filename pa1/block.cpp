//
// CPSC 221 Section 201
// Programming Assignment 1
//

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "block.h"

using namespace cs221util;
using namespace std;


// int Dimension() const;
// Returns the dimensions of the block.
// Note that the horizontal and vertical dimensions are the same.
int Block::Dimension() const {
  return data.size();
}

// void Build(PNG & im, int upper, int left, int dimension);
// Completes a block’s pixel data from the square area of dimension by dimension
// pixels in im whose upper-left corner is at position (left,upper).
void Block::Build(PNG & im, int upper, int left, int dimension) {
  // version 1
  for(int i = left; i < left+dimension; i++) {
    std::vector<HSLAPixel> v;
    for(int j = upper; j < upper+dimension; j++) {
      HSLAPixel* pix = im.getPixel(i,j);
      v.push_back(*pix);
    }
    data.push_back(v);
  }

  // version 2
  // data.resize(dimension);
  // for(int i = 0; i < dimension; i++) {
  //   data[i].resize(dimension);
  //   for(int j = 0; j < dimension; j++) {
  //     HSLAPixel* pix = im.getPixel(i+upper, j+left);
  //     data[i][j] = *pix;
  //   }
  // }
}

// void Render(PNG & im, int x, int y ) const;
// Draws the block at position (x,y) in im.
void Block::Render(PNG & im, int x, int y) const {
  for(unsigned int i = x; i < x+data.size(); i++) {
    for(unsigned int j = y; j < y+data.size(); j++) {
      *im.getPixel(i,j) = data[i-x][j-y];
    }
  }
}

// void Negative();
// Reverses the hue and luminance of every pixel in the block,
// creating a simulated photo-negative effect. It is up to you to study
// the HSLAPixel documentation to decide what an appropriate meaning for
// reversing hue and luminance will be.
void Block::Negative() {
  for(unsigned int i = 0; i < data.size(); i++) {
    for(unsigned int j = 0; j < data.size(); j++) {
      HSLAPixel* pix = &data[i][j];
      // get the hue
      if((pix->h + 180) >= 360) {
        pix->h = (pix->h + 180) - 360;
      } else {
        pix->h = pix->h + 180;
      }
      // get the luminance
      pix->l = 1 - pix->l;
    }
  }
}
