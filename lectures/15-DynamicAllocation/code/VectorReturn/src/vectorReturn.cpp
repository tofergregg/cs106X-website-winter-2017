/*
 * CS 106B, Chris Gregg
 *
 * This program contains code to demonstrate pointers.
 *
 * NOTE 1: This program will compile with warnings due to uninitialized variables.
 * Note 2: This program will crash (purposefully) on some choices.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"

using namespace std;

Vector<int> *squares(int numSquares) {
    Vector<int> *vec = new Vector<int>; // dynamically allocate memory
    for (int i=0; i < numSquares; i++) {
        vec->add(i * i); // arrow notation!
    }
    return vec;
}

int main() {
    Vector<int> *vec = squares(100);
    cout << *vec << endl; // dereference
    // clean up!
    delete vec;
    return 0;
}
