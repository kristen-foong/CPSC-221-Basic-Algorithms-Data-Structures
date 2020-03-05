#define MAIN

#include "main.cpp"
#include "catch_config.h"

using namespace std;

int compareFile(string f1, string f2) {

    FILE *a = fopen(f1.c_str(), "r");
    FILE *b = fopen(f2.c_str(), "r");
    char buf1[10000], buf2[10000];
    do {
        size_t r1 = fread(buf1, 1, 10000, a);
        size_t r2 = fread(buf2, 1, 10000, b);

        if (r1 != r2 ||
            memcmp(buf1, buf2, r1)) {
            return 0;  // Files are not equal
        }
    } while (!feof(a) && !feof(b));
    int ret = feof(a) && feof(b);
    fclose(a);
    fclose(b);
    return ret;
}


#define test(a, b) TEST_CASE(a) {\
    std::ofstream out(string("output/") + a);\
    std::streambuf *coutbuf = std::cout.rdbuf(); \
    std::cout.rdbuf(out.rdbuf()); \
    (*b)();\
    std::cout.rdbuf(coutbuf);\
    REQUIRE(compareFile(string("output/") + a, string("expected/") + a));\
}

test("testRotateLeft.out", &testRotateLeft);

test("testRotateRight.out", &testRotateRight);

test("testRotateLeftRight.out", &testRotateLeftRight);

test("testRotateRightLeft.out", &testRotateRightLeft);

test("testManyInsertions.out", &testManyInsertions);

test("testManyRemovals.out", &testManyRemovals);