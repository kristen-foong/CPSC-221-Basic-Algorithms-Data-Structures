// File:        main.cpp
// Date:        2020-01-18 00:13
// Description: Contains basic tests for GridList
//              Further test cases to follow later
//              Please see images in "output" folder as samples for correct output

#include "gridlist.h"

void TestBlockNegative();
void TestCheckerN();
void TestSandwichH();
void TestSandwichV();
void TestCheckerSwap();

int main()
{
  TestBlockNegative();
  TestCheckerN();
  TestSandwichH();
  TestSandwichV();
  TestCheckerSwap();

  #ifdef _WIN32
  system("pause");
  #endif
  return 0;
}

void TestBlockNegative()
{
  PNG cmkm;
  cmkm.readFromFile("images/cmkm.png");
  Block b;
  b.Build(cmkm, 0, 0, 480);
  b.Negative();
  
  PNG cmkm_n = cmkm;
  b.Render(cmkm_n, 0, 0);
  cmkm_n.writeToFile("images/cmkm_n.png");
}

void TestCheckerN()
{
  PNG bike;
  bike.readFromFile("images/cb650r.png");
  GridList bikelist(bike, 100);
  bikelist.CheckerN();

  PNG checkerbike = bikelist.Render();
  checkerbike.writeToFile("images/cb650r_checker_n.png");
}

void TestSandwichH()
{
  PNG bread;
  bread.readFromFile("images/bread.png");
  GridList breadlist(bread, 40);

  PNG roast;
  roast.readFromFile("images/roast.png");
  GridList roastlist(roast, 40);

  breadlist.Sandwich_H(roastlist);

  PNG roast_sandwich = breadlist.Render();
  roast_sandwich.writeToFile("images/roast_sandwich_h.png");
}

void TestSandwichV()
{
  PNG bread;
  bread.readFromFile("images/bread.png");
  GridList breadlist(bread, 40);

  PNG pickle;
  pickle.readFromFile("images/pickle.png");
  GridList picklelist(pickle, 40);

  breadlist.Sandwich_V(picklelist);

  PNG pickle_sandwich = breadlist.Render();
  pickle_sandwich.writeToFile("images/pickle_sandwich_v.png");
}

void TestCheckerSwap()
{
  PNG mixed;
  mixed.readFromFile("images/160x120_mixed.png");
  GridList mixedlist(mixed, 40);

  PNG solid;
  solid.readFromFile("images/160x120_solid.png");
  GridList solidlist(solid, 40);

  mixedlist.CheckerSwap(solidlist);

  PNG mixed_swap = mixedlist.Render();
  PNG solid_swap = solidlist.Render();
  mixed_swap.writeToFile("images/mixed_swap.png");
  solid_swap.writeToFile("images/solid_swap.png");
}