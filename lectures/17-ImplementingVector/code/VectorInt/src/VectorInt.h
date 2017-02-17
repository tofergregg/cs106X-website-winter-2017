// VectorInt.h
// Header file for our Vector of ints Class

#pragma once

#include<ostream>
using namespace std;

const int INITIAL_CAPACITY = 8;

class VectorInt {
public:
    // constructor
    VectorInt();

    // destructor
    ~VectorInt();

    // append value at end
    void add(int value);

    // insert a value at index
    void insert(int index, int value);

    // return value at index
    int get(int index);

    // remove value at index
    void remove(int index);

    // return the number of elements in the array
    int size();

    // true if zero elements
    bool isEmpty();

    // overload <<
    friend ostream& operator<<(ostream &out, VectorInt &vec);
private:
    // array of elements
    int *elements;
    int capacity;
    int count;

    void expand();
};
