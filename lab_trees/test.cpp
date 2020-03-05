#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binarytree.h"

TEST_CASE("sumdistances::basic","[weight=2][part=tree]"){
	BinaryTree<int> tree;
    tree.insert(0);
    tree.insert(-1, true);
    tree.insert(1, true);
    REQUIRE(tree.sumDistances() == 2);
}

TEST_CASE("sumdistances::stick","[weight=2][part=tree]"){
	BinaryTree<int> stick;
    int sum = 0;
    int cur = 0;
    stick.insert(0);
    for (int i = 1; i < 10; ++i) {
        sum += (++cur);
        stick.insert(i, true); //insert ordered
        REQUIRE(stick.sumDistances() == sum);
    }
    REQUIRE(stick.sumDistances() == 45);
}