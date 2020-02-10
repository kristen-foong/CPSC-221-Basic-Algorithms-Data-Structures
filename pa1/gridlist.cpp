// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const
{
  PNG image;
  // enter your code here
  int dim = northwest->data.Dimension();
  image.resize(dimx*dim, dimy*dim);
  if(northwest == NULL) {
    cout << "got null northwest" << endl;
    return image;
  }
  GridNode* curr = northwest;
  for(int j = 0; j < dimy; j++) {
    for(int i = 0; i < dimx; i++) {
      Block b = curr->data;
      b.Render(image,i,j);
      curr = curr->next;
    }
  }
  return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block& bdata)
{
  // enter your code here
  GridNode* newNode = new GridNode(bdata);
  if(IsEmpty()) {
    northwest = newNode;
    southeast = newNode;
  } else {
    GridNode* temp = southeast;
    temp->next = newNode;
    newNode->prev = temp;
    southeast = newNode;
  }
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList& inner)
{
  // enter your code here
  if(inner.dimy != dimy || inner.dimy < 1 || dimy <2) {
    return;
  }

  int divide = dimx / 2;
  int trackX = 0;
  int inCount = 0;
  int count = 0;

  if(inner.dimy == dimy) {
    cout << "in sandwich_h" << endl;
    GridNode* curr = northwest;
    GridNode* inCurr = inner.northwest;
    GridNode* temp;
    GridNode* innerTemp;
    while (curr != NULL) {
      trackX = count % dimx;
      if(trackX == divide-1) {
        temp = curr->next;
        curr->next = inCurr;
        inCurr->prev = curr;
        while((inCount % inner.dimx) != (inner.dimx - 1)) {
          inCurr = inCurr->next;
          inCount++;
        }
        innerTemp = inCurr->next;
        inCurr->next = temp;
        temp->prev = inCurr;
        inCurr = innerTemp;
        curr = temp;
        inCount++;
      } else {
        curr = curr->next;
      }
      count++;
    }
    dimx = dimx + inner.dimx;
    inner.northwest = NULL;
    inner.southeast = NULL;
    inner.dimx = 0;
    inner.dimy = 0;
  }

}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList& inner)
{
  // enter your code here
  if(inner.dimx != dimx || inner.dimx < 1 || dimx <2) {
    return;
  }

  int divide = dimy / 2;
  int trackY = 0;
  int inCount = 0;
  int count = 0;

  if(inner.dimx == dimx) {
    cout << "in sandwich_v" << endl;
    GridNode* curr = northwest;
    GridNode* inCurr = inner.northwest;
    GridNode* temp;
    GridNode* innerTemp;
    while (curr != NULL) {
      if(count == dimx) {
        count = 0;
        trackY++;
      }
      if(trackY == divide) {
        temp = curr->next;
        curr->next = inCurr;
        inCurr->prev = curr;
        while (inCurr->next != NULL) {
          inCurr = inCurr->next;
          cout << "in inner while" << endl;
        }
        // innerTemp = inCurr->next;
        inCurr->next = temp;
        temp->prev = inCurr;
        curr = temp;
        // inCurr = innerTemp;
        trackY++;
      } else {
        curr = curr->next;
      }
      count++;
    }
    dimy = dimy + inner.dimy;
    inner.northwest = NULL;
    inner.southeast = NULL;
    inner.dimx = 0;
    inner.dimy = 0;
  }

}


// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList& otherlist)
{
  // enter your code here
  if(dimx != otherlist.dimx || dimy != otherlist.dimy) {
    return;
  }

  if(dimx % 2 == 1) {
    GridNode* curr = northwest;
    GridNode* oCurr = otherlist.northwest;
    while(curr != NULL) {
      GridNode* temp = curr->next;
      GridNode* temp2 = oCurr->next;
      curr->next = oCurr;
      oCurr->prev = curr;
      curr = temp;
      oCurr = temp2;
    }
  }
}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN()
{
  // enter your code here
  GridNode* curr = northwest;
  if(northwest == NULL) {
    return;
  }
  // odd number width
  if(dimx % 2 == 1) {
    int n = 0;
    while(curr != NULL) {
      if(n%2 == 1) {
        curr->data.Negative();
      }
      curr = curr->next;
      n++;
    }
  } else {
    // even number width
    for(int j = 0; j < dimy; j++) {
      for(int i = 0; i < dimx; i++) {
        if(j % 2 == 0 && i % 2 == 1) {
          curr->data.Negative();
        } else if (j % 2 == 1 && i % 2 == 0) {
          curr->data.Negative();
        }
        curr = curr->next;
      }
    }
  }

}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear()
{
  // enter your code here
  // GridNode* curr = northwest->next;
  // while(curr != NULL) {
  //   delete curr->prev;
  //   curr->prev = NULL;
  //   curr = curr->next;
  // }
  // delete southeast;
  // southeast = NULL;
}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList& otherlist)
{
  // enter your code here
  // GridNode* add = otherlist.northwest;
  // while(add->next != otherlist.southeast) {
  //   InsertBack(add->next->data);
  // }
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//
