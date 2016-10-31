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

using namespace std;

void mystery(int a, int& b, int* c) {
    a++;
    (*c)--;
    b += *c;
    cout << a << " " << b << " " << *c << " " << endl;
}

int main() {
    int a = 4;
    int b = 8;
    int c = -3;
    cout << a << " " << b << " " << c << " " << endl;
    mystery(c, a, &b);
    cout << a << " " << b << " " << c << " " << endl;
    int pages[a];
    cout << pages[0] << endl;
    return 0;
}
