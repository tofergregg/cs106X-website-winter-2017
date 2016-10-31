/*
 * CS 106B, Chris Gregg
 *
 * This program contains code to demonstrate deleting and
 * some things you have to be aware of when using delete.
 */

// To make:
// g++ -g -O0 deleteExample.cpp -o deleteExample
//
// To run:
// ./deleteExample
//
// To run with Valgrind to see the memory errors:
// (must run on Myth: to log into Myth:
// ssh your_SUID@myth.stanford.edu
//
// valgrind -v ./deleteExample

#include <iostream>
//#include "console.h"

using namespace std;

void printArray(int *array, int length);
void arrayFun(int *origArray, int length);
int *badCopy(int *array, int length);

int main() {
    int array[3] = {1,5,7}; // construct a static array
    arrayFun(array, 3);

    int longArray[10000];
    for (int i=0; i < 10000; i++) {
        longArray[i] = i;
    }
    // we're going to be in trouble here
    // This might work temporarily, but because the
    // memory is already released, the OS is welcome
    // to give it to another program before we
    // try and use it again! Our printArray()
    // may or may not work...bad news!
    int *longArrayCopy = badCopy(longArray,10000);
    printArray(longArrayCopy,10000);
    return 0;
}

void arrayFun(int *origArray, int length) {
    // allocate space for a new array
    int *multiple = new int[length];
    for (int i=0; i < length; i++) {
        multiple[i] = origArray[i] * 2; // double each value
    }
    printArray(multiple, length); // prints each value doubled
    delete [] multiple; // give back the memory

    multiple = new int[length * 2]; // now twice as many
    for (int i=0; i < length; i++) {
        multiple[i*2] = origArray[i] * 2; // double each value
        multiple[i*2+1] = origArray[i] * 3; // triple the value
    }
    // if the original looks like this:
    //   [1,5,7]
    // multiple now looks like this:
    // [2,3,10,15,14,21]
    printArray(multiple, length * 2);
    delete [] multiple; // clean up
}

// BAD BAD BAD
// This function returns memory that has been deleted already!
// Not good!
int *badCopy(int *array, int length) {
    int *arrCopy = new int[length];
    for (int i=0; i < length; i++) {
        arrCopy[i] = array[i];
    }
    delete [] arrCopy;
    return arrCopy; // too late! Memory has been released.
}

void printArray(int *array, int length) {
    cout << "[";
    for (int i=0; i < length; i++) {
        cout << array[i];
        if (i < length-1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

