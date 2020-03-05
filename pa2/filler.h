/**
 * @file filler.h
 * Defintion of a filler namespace.
 *
 */
#ifndef _FILLER_H_
#define _FILLER_H_

#include <iostream>

#include "cs221util/PNG.h"

#include "animation.h"
#include "center.h"
#include "colorPicker.h"
#include "point.h"
#include "queue.h"
#include "stack.h"

using namespace std;
using namespace cs221util;

/**
 * filler namespace: specifies a set of functions for performing flood
 * fills on images.
 *
 */
namespace filler
{

/**
 * Struct to store configuration variables for filler function.
 * The length of the vectors `centers` and `pickers` should match.
 * We don't check this but you will likely get a segfault or other bugs if the lengths differ.
 * Each entry in `centers` is the seed location used for the flood fill by
 * the colorPicker at the corresponding location in `pickers`.
 */
struct FillerConfig
{
    int frameFreq;                 // Frequency with which to save frames to GIF animation.
    float tolerance;               // Tolerance used to determine if pixel is in fill region.
    PNG img;                       // Image to perform the fill on.
    vector<center> centers;        // Seed locations where the fill will begin.
    vector<colorPicker *> pickers; // colorPickers used to fill the regions.
};

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill.
 * @return animation  Object illustrating progression of flood fill algorithm.
 */
animation fillBFS(FillerConfig &config);

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill.
 * @return animation  Object illustrating progression of flood fill algorithm.
 */
animation fillDFS(FillerConfig &config);

/**
 * Run a multi-point flood fill on an image.
 *
 * @param  config     FillerConfig struct with data for flood fill of image.
 * @return animation  Object illustrating progression of flood fill algorithm.
 */
template <template <class T> class OrderingStructure> animation fill(FillerConfig &config);

// Add any helper functions here

} // namespace filler

#include "filler.cpp"

#endif
