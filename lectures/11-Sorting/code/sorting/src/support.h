/*
 * CS 106B, Marty Stepp
 * This file contains supporting code that we used to help
 * us with searching and sorting.
 * We did not write this code in class.
 */

#ifndef _support_h
#define _support_h

#include "vector.h"

// function prototype declarations
void fillRandomIntVector(Vector<int>& v, int length);
void fillSortedIntVector(Vector<int>& v, int length);
bool isSorted(const Vector<int>& v);
void swap(Vector<int>& v, int i, int j);

#endif
