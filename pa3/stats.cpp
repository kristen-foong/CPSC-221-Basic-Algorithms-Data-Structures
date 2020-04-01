
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
	for(unsigned int x = 0; x < im.width(); x++) {
		for(unsigned int y = 0; y < im.height(); y++) {
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

	// sumGreen
	for(unsigned int x = 0; x < im.width(); x++) {
		for(unsigned int y = 0; y < im.height(); y++) {
			RGBAPixel *pix = im.getPixel(x,y);
			if(x == 0 && y == 0) {
				sumGreen[x][y] = pix->g;
			} else if (y == 0) {
				sumGreen[x][y] = sumGreen[x-1][y] + pix->g;
			} else if (x == 0) {
				sumGreen[x][y] = sumGreen[x][y-1] + pix->g;
			} else {
				sumGreen[x][y] = sumGreen[x-1][y] + sumGreen[x][y-1] - sumGreen[x-1][y-1] + pix->g;
			}
		}
	}

	// sumBlue
	for(unsigned int x = 0; x < im.width(); x++) {
		for(unsigned int y = 0; y < im.height(); y++) {
			RGBAPixel *pix = im.getPixel(x,y);
			if(x == 0 && y == 0) {
				sumBlue[x][y] = pix->b;
			} else if (y == 0) {
				sumBlue[x][y] = sumBlue[x-1][y] + pix->b;
			} else if (x == 0) {
				sumBlue[x][y] = sumBlue[x][y-1] + pix->b;
			} else {
				sumBlue[x][y] = sumBlue[x-1][y] + sumBlue[x][y-1] - sumBlue[x-1][y-1] + pix->g;
			}
		}
	}

	// sumsqRed
	for(unsigned int x = 0; x < im.width(); x++) {
		for(unsigned int y = 0; y < im.height(); y++) {
			RGBAPixel *pix = im.getPixel(x,y);
			if(x == 0 && y == 0) {
				sumRed[x][y] = (pix->r)*(pix->r);
			} else if (y == 0) {
				sumRed[x][y] = sumRed[x-1][y] + ((pix->r)*(pix->r));
			} else if (x == 0) {
				sumRed[x][y] = sumRed[x][y-1] + ((pix->r)*(pix->r));
			} else {
				sumRed[x][y] = sumRed[x-1][y] + sumRed[x][y-1] - sumRed[x-1][y-1] + ((pix->r)*(pix->r));
			}
		}
	}

	// sumsqGreen
	for(unsigned int x = 0; x < im.width(); x++) {
		for(unsigned int y = 0; y < im.height(); y++) {
			RGBAPixel *pix = im.getPixel(x,y);
			if(x == 0 && y == 0) {
				sumGreen[x][y] = (pix->g)*(pix->g);
			} else if (y == 0) {
				sumGreen[x][y] = sumGreen[x-1][y] + ((pix->g)*(pix->g));
			} else if (x == 0) {
				sumGreen[x][y] = sumGreen[x][y-1] + ((pix->g)*(pix->g));
			} else {
				sumGreen[x][y] = sumGreen[x-1][y] + sumGreen[x][y-1] - sumGreen[x-1][y-1] + ((pix->g)*(pix->g));
			}
		}
	}

	// sumsqBlue
	for(unsigned int x = 0; x < im.width(); x++) {
		for(unsigned int y = 0; y < im.height(); y++) {
			RGBAPixel *pix = im.getPixel(x,y);
			if(x == 0 && y == 0) {
				sumBlue[x][y] = (pix->b)*(pix->b);
			} else if (y == 0) {
				sumBlue[x][y] = sumBlue[x-1][y] + ((pix->b)*(pix->b));
			} else if (x == 0) {
				sumBlue[x][y] = sumBlue[x][y-1] + ((pix->b)*(pix->b));
			} else {
				sumBlue[x][y] = sumBlue[x-1][y] + sumBlue[x][y-1] - sumBlue[x-1][y-1] + ((pix->b)*(pix->b));
			}
		}
	}


}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

	// YOUR CODE HERE!!
	long sum = 0;

	if(channel == 'r') {
		long rhc = sumRed[lr.first][lr.second];
		if(ul.first == 0 && ul.second == 0) {
			return rhc;
		} else if (ul.first == 0) {
			sum = rhc - sumRed[ul.first-1][lr.second] - sumRed[lr.first][ul.second-1] + sumRed[ul.first-1][ul.second-1];
		} else if (ul.second == 0) {
			sum = rhc - sumRed[ul.first-1][lr.second];
		} else {
			sum = rhc - sumRed[ul.first-1][lr.second] - sumRed[lr.first][ul.second-1] + sumRed[ul.first-1][ul.second-1];
		}
	} else if (channel == 'g') {
		long rhc = sumGreen[lr.first][lr.second];
		if(ul.first == 0 && ul.second == 0) {
			return rhc;
		} else if (ul.first == 0) {
			sum = rhc - sumGreen[ul.first-1][lr.second] - sumGreen[lr.first][ul.second-1] + sumGreen[ul.first-1][ul.second-1];
		} else if (ul.second == 0) {
			sum = rhc - sumGreen[ul.first-1][lr.second];
		} else {
			sum = rhc - sumGreen[ul.first-1][lr.second] - sumGreen[lr.first][ul.second-1] + sumGreen[ul.first-1][ul.second-1];
		}
	} else {
		long rhc = sumBlue[lr.first][lr.second];
		if(ul.first == 0 && ul.second == 0) {
			return rhc;
		} else if (ul.first == 0) {
			sum = rhc - sumBlue[ul.first-1][lr.second] - sumBlue[lr.first][ul.second-1] + sumBlue[ul.first-1][ul.second-1];
		} else if (ul.second == 0) {
			sum = rhc - sumBlue[ul.first-1][lr.second];
		} else {
			sum = rhc - sumBlue[ul.first-1][lr.second] - sumBlue[lr.first][ul.second-1] + sumBlue[ul.first-1][ul.second-1];
		}
	}
	return sum;

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

	// YOUR CODE HERE!!
	long sum = 0;

	if(channel == 'r') {
		long rhc = sumsqRed[lr.first][lr.second];
		if(ul.first == 0 && ul.second == 0) {
			return rhc;
		} else if (ul.first == 0) {
			sum = rhc - sumsqRed[ul.first-1][lr.second] - sumsqRed[lr.first][ul.second-1] + sumsqRed[ul.first-1][ul.second-1];
		} else if (ul.second == 0) {
			sum = rhc - sumsqRed[ul.first-1][lr.second];
		} else {
			sum = rhc - sumsqRed[ul.first-1][lr.second] - sumsqRed[lr.first][ul.second-1] + sumsqRed[ul.first-1][ul.second-1];
		}
	} else if (channel == 'g') {
		long rhc = sumsqGreen[lr.first][lr.second];
		if(ul.first == 0 && ul.second == 0) {
			return rhc;
		} else if (ul.first == 0) {
			sum = rhc - sumsqGreen[ul.first-1][lr.second] - sumsqGreen[lr.first][ul.second-1] + sumsqGreen[ul.first-1][ul.second-1];
		} else if (ul.second == 0) {
			sum = rhc - sumsqGreen[ul.first-1][lr.second];
		} else {
			sum = rhc - sumsqGreen[ul.first-1][lr.second] - sumsqGreen[lr.first][ul.second-1] + sumsqGreen[ul.first-1][ul.second-1];
		}
	} else {
		long rhc = sumsqBlue[lr.first][lr.second];
		if(ul.first == 0 && ul.second == 0) {
			return rhc;
		} else if (ul.first == 0) {
			sum = rhc - sumsqBlue[ul.first-1][lr.second] - sumsqBlue[lr.first][ul.second-1] + sumsqBlue[ul.first-1][ul.second-1];
		} else if (ul.second == 0) {
			sum = rhc - sumsqBlue[ul.first-1][lr.second];
		} else {
			sum = rhc - sumsqBlue[ul.first-1][lr.second] - sumsqBlue[lr.first][ul.second-1] + sumsqBlue[ul.first-1][ul.second-1];
		}
	}
	return sum;
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
	long width = (lr.first+1) - ul.first;
	long height = (lr.second+1) - ul.second;
	return width*height;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
	long area = rectArea(ul, lr);
	long rsq = getSumSq('r', ul, lr);
	long gsq = getSumSq('g', ul, lr);
	long bsq = getSumSq('b', ul, lr);
	long sumsq = rsq + gsq + bsq;
	long dev = (rsq*rsq) + (gsq*gsq) + (bsq*bsq);
	long score = sumsq - (dev/area);
	return score;

}

RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
	RGBAPixel pix;
	long area = rectArea(ul, lr);
	pix.r = getSum('r', ul, lr)/area;
	pix.g = getSum('g', ul, lr)/area;
	pix.b = getSum('b', ul, lr)/area;
	return pix;

}
