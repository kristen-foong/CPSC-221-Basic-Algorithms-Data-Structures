/**
 * @file main.cpp
 * Contains code to test your recursion, stack, and queue problems.
 */

#include <unistd.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include "quackfun.h"
#include "exercises.h"
#include "catch_config.h"

using namespace std;

TEST_CASE("==== sumDigits ===="){
    SECTION("sumDigits(243) == 9") {
        REQUIRE(RecursionExercises::sumDigits(243) == 9);
    }
    SECTION("sumDigits(49) == 13"){
        REQUIRE(RecursionExercises::sumDigits(49) == 13);
    }
    SECTION("sumDigits(1) == 1"){
        REQUIRE(RecursionExercises::sumDigits(1) == 1);
    }
    SECTION("sumDigits(0) == 0"){
        REQUIRE(RecursionExercises::sumDigits(0) == 0);
    }
}

TEST_CASE("==== triangle ===="){
    SECTION("triangle(0) == 0"){
        REQUIRE(RecursionExercises::triangle(0) == 0);
    }
    SECTION("triangle(3) == 6"){
        REQUIRE(RecursionExercises::triangle(3) == 6);
    }
    SECTION("triangle(6) == 21"){
        REQUIRE(RecursionExercises::triangle(6) == 21);
    }
}

TEST_CASE("==== sum ===="){
    stack<int> s;

    const int n = 16;
    for (int i = 0; i <= n; i++)
        s.push(i);

    stack<int> orig = s;
    REQUIRE(QuackFun::sum<int>(s) == 136);
    REQUIRE(s == orig);
}

TEST_CASE("==== scramble ===="){
    queue<int> q;
    for (int i = 0; i <= 16; i++)
        q.push(i);

    QuackFun::scramble<int>(q);

    int expected[] = {0, 2, 1, 3, 4, 5, 9, 8, 7, 6, 10, 11, 12, 13, 14, 16, 15};
    for (int i = 0; i <= 16; i++) {
        REQUIRE(q.front() == expected[i]);
        q.pop();
    }
}

TEST_CASE("==== verifySame ===="){
    stack<int> s, s1, s2;
    queue<int> q, q1, q2;
    SECTION("verifySame(true)") {
        for (int i = 0; i < 5; i++) {
            s1.push(i);
            q1.push(i);
        }
        q = q1;
        s = s1;
        REQUIRE(QuackFun::verifySame(s, q));
        REQUIRE(q == q1);
        REQUIRE(s == s1);
    }
    SECTION("verifySame(false)") {
        for (int i = 0; i < 4; i++) {
            s2.push(i + 1);
            q2.push(i);
        }
        s2.push(5);
        q2.push(5);

        q = q2;
        s = s2;
        REQUIRE(QuackFun::verifySame(s, q)==false);
        REQUIRE(q == q2);
        REQUIRE(s == s2);
    }
}