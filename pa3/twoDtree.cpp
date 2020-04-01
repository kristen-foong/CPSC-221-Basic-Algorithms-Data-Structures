
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){

	// YOUR CODE HERE
	height = imIn.height();
	width = imIn.width();
	pair<int, int> ul = make_pair(0,0);
	pair<int, int> lr = make_pair(width-1, height-1);
	stats s(imIn);
	bool v = true;
	root = buildTree(stat, ul, lr, v);

}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {

	// YOUR CODE HERE!!

}

PNG twoDtree::render(){

// YOUR CODE HERE!!

}

int twoDtree::idealPrune(int leaves){

// YOUR CODE HERE!!

}

int twoDtree::pruneSize(int tol){

// YOUR CODE HERE!!

}

void twoDtree::prune(int tol){

// YOUR CODE HERE!!

}

void twoDtree::clear() {

// YOUR CODE HERE!!

}

void twoDtree::copy(const twoDtree & orig){

// YOUR CODE HERE!!

}
