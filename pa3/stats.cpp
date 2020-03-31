
#include "stats.h"

stats::stats(PNG & im){

// YOUR CODE HERE!!
int w = im.width();
int h = im.height();
sumRed.resize(w, vector<long>(h));
sumGreen.resize(w, vector<long>(h));
sumBlue.resize(w, vector<long>(h));
sumsqRed.resize(w, vector<long>(h));
sumsqGreen.resize(w, vector<long>(h));
sumsqBlue.resize(w, vector<long>(h));

// sumRed
for(int x = 0; x < im.width(); x++) {
	for(int y = 0; y < im.height(); y++) {
		RGBAPixel *pix = im.getPixel(x,y);
		if(x == 0 && y == 0) {
			sumRed[x][y] = pix->r;
		} else if (y == 0) {
			sumRed[x][y] = sumRed[x-1][y] + pix->r;
		} else if (x == 0) {
			sumRed[x][y] = sumRed[x][y-1] + pix->r;
		} else {
			sumRed[x][y] = sumRed[x-1][y] + sumRed[x][y-1] - sumRed[x-1][y-1] + pix->r;
		}
	}
}

}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
for(int x = ul.first; x < lr.first; x++) {
	for(int y = ul.second; y < lr.second; y++) {

	}
}

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}

RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}
