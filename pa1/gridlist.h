// File:        gridlist.h
// Date:        2020-01-18 00:15
// Description: Definition of a GridList class, for CPSC 221 2019W2 PA1
//
// DO NOT MODIFY ANY EXISTING DEFINITIONS
// BUT YOU MAY ADD YOUR OWN PRIVATE MEMBER FUNCTIONS IF NECESSARY
//

#ifndef _GRIDLIST_H_
#define _GRIDLIST_H_

#include "block.h"

using namespace std;

// For best coding practices, the GridNode class should be private to the GridList class via
// encapsulation - the end user does not need to know our
// node-based implementation details
// However, for this PA, GridNode will be made public so that we are able to test the structure
// of your lists.
class GridNode {
public:
  Block data; // data held by GridNode

  GridNode(); // default constructor
  GridNode(const Block& bdata);
  GridNode* prev; // pointer to previous node in list, if one exists. NULL otherwise
  GridNode* next; // pointer to next node in list, if one exists. NULL otherwise
};

class GridList {
  private:

    // GridList private member variables

    GridNode* northwest; // pointer to first (upper-left) node in the grid
    GridNode* southeast; // pointer to last (lower-right) node in the grid
    int dimx; // horizontal dimension of grid (in blocks)
    int dimy; // vertical dimension of grid (in blocks)

    // GridList private member functions
    void Clear();
    void Copy(const GridList& otherlist);

    // YOU MAY ADD YOUR OWN PRIVATE MEMBER FUNCTION DEFINITIONS HERE
    //
    //
    //

  public:

    // GridList public member functions
    GridList();
    GridList(PNG& img, int blockdim);
    GridList(const GridList& otherlist);
    GridList& operator=(const GridList& rhs);
    ~GridList();

    int Length() const;
    bool IsEmpty() const;
    PNG Render() const;

    void InsertBack(const Block& bdata);
    void Sandwich_H(GridList& inner);
    void Sandwich_V(GridList& inner);
    void CheckerN();
    void CheckerSwap(GridList& otherlist);

    // for testing only
    GridNode* getNorthWest();
    GridNode* getSouthEast();
};

#endif