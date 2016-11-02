// VectorInt.cpp
// Implementation of our Vector of ints class

#include "VectorInt.h"

// constructor
VectorInt::VectorInt() {
    capacity = INITIAL_CAPACITY;
    count = 0;
    elements = new int[capacity];
}

// destructor
VectorInt::~VectorInt() {
    delete [] elements;
}

// append value at end
void VectorInt::add(int value) {
    if (count == capacity) {
        expand();
    }
    // add to end of array
    elements[count] = value;
    count++;
}

// insert a value at index
void VectorInt::insert(int index, int value) {
    if (count == capacity) {
        expand();
    }
    // move elements after index to the right
    for (int i=count; i > index; i--) {
        elements[i] = elements[i-1];
    }
    elements[index] = value;
    count++;
}

// return value at index
int VectorInt::get(int index) {
    return elements[index];
}

// remove value at index
void VectorInt::remove(int index) {
    for (int i=index; i < count; i++) {
        elements[i] = elements[i+1];
    }
    count--;
}

// return the number of elements in the array
int VectorInt::size() {
    return count;
}

// true if zero elements
bool VectorInt::isEmpty() {
    return count == 0;
}

// overload <<
ostream &operator<<(ostream &out, VectorInt &vec) {
    out << "[";
    for (int i=0; i < vec.count; i++) {
       out << vec.elements[i];
       if (i < vec.count - 1) {
           out << ", ";
       }
    }
    out << "]";
    return out;
}

// expand
void VectorInt::expand() {
    // 1. create space for new array
    int *newElements = new int[capacity * 2];

    // 2. copy the elements
    for (int i=0; i < count; i++) {
       newElements[i] = elements[i];
    }

    // 3. delete old array
    delete [] elements;

    // 4. point elements to new array
    elements = newElements;

    // 5. update capacity
    capacity *= 2;
}
