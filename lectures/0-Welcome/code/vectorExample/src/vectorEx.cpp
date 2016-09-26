// Insert even integers into a Vector

#include <iostream>
#include "console.h" // Stanford library
#include "vector.h"  // Stanford library

using namespace std;

const int NUM_ELEMENTS = 10;

int main() {
    Vector<int> myVec;
    // add the even ints to the vector
    for (int i=0; i< NUM_ELEMENTS; i++) {
       myVec.add(i*2);
    }

    // print out the whole vector
    for (int i : myVec) {
        cout << i << endl;
    }
    return 0;
}

