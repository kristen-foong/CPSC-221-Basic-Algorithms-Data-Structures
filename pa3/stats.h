
#ifndef _STATS_H
#define _STATS_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>
using namespace std;
using namespace cs221util;

class stats {

private:
	vector< vector< long >> sumRed;
	vector< vector< long >> sumGreen;
	vector< vector< long >> sumBlue;
	vector< vector< long >> sumsqRed;
	vector< vector< long >> sumsqGreen;
	vector< vector< long >> sumsqBlue;

	/* returns the sums of all pixel values across all color channels.
	* useful in computing the score of a rectangle
	* PA3 function
	* @param channel is one of r, g, or b
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
	long getSum(char channel, pair<int,int> ul, pair<int,int> lr);

	/* returns the sums of squares of all pixel values across all color channels.
	* useful in computing the score of a rectangle
	* PA3 function
	* @param channel is one of r, g, or b
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
	long getSumSq(char channel, pair<int,int> ul, pair<int,int> lr);

public:

	// initialize the private vectors so that, for each color,  entry 
	// (x,y) is the cumulative sum of the the color values from (0,0)
	// to (x,y). Similarly, the sumSq vectors are the cumulative
	// sum of squares from (0,0) to (x,y).
	stats(PNG & im); 

	// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
	long getScore(pair<int,int> ul, pair<int,int> lr);

	// given a rectangle, return the average color value over the rectangle as a pixel.
	/* Each color component of the pixel is the average value of that component over
	* the rectangle.
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
	RGBAPixel getAvg(pair<int,int> ul, pair<int,int> lr);

	// given a rectangle, return the number of pixels in the rectangle
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
	long rectArea(pair<int,int> ul, pair<int,int> lr);

};

#endif
