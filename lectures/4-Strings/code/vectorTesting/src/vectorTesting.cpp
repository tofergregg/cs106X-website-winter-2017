#include <iostream>
#include "console.h"
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "timer.h"   // for timer calculations
#include "random.h"  // for random entries into the Vector
using namespace std;

void runTests(int choice);
long vectorTest(int numElements, int function, int numTests);
long vecAdd(Vector<int> &vec, int value, int numTests);
long vecInsert(Vector<int> &vec, int value, int numTests);
long vecRemove(Vector<int> &vec, int index, int numTests);
long vecRemoveFast(Vector<int> &vec, int index, int numTests);

int main() {
    int choice = -1;
    while (choice != 0) {
        cout << "Welcome to the Vector Tester" << endl;
        cout << "Please choose a test:" << endl;
        cout << "1) add(x)" << endl;
        cout << "2) insert(0,x)" << endl;
        cout << "3) remove(index)" << endl;
        cout << "4) removeFast(index)" << endl;
        int choice = getInteger("Choose 1-4, or 0 to quit: ","Please choose an integer! ");
        runTests(choice);
    }
    return 0;
}

// run each test for 2^15, 2^16,...,2^28
void runTests(int choice) {
    cout << "Test: " << endl;
    switch(choice) {
    case 1:
        cout << "add(x)" << endl;
        break;
    case 2:
        cout << "insert(0,x)" << endl;
        break;
    case 3:
        cout << "remove(index)" << endl;
        break;
    case 4:
        cout << "removeFast(index)" << endl;
    }
    cout << "Results in milliseconds" << endl;

    for (int n=(1<<16); n <= (1 << 28); n = (n+1)*2) {
        long avgElapsedTime;
        cout << "n = \t" << n << "\t" << flush; // prints immediately
        avgElapsedTime = vectorTest(n,choice,5); // do ten tests to get an average
        cout << avgElapsedTime << endl;
    }
}

// Reports the time to perform a function on numElements number of elements
// function can be:
// 1) add(x), adds 10 values to the end of the array
// 2) insert(0,x), inserts 10 values at the beginning of the array
// 3) remove(index), where index will be half way through the Vector
//    removes 10 values at position index
// 4) removeFast(index), where index will be half way through the Vector,
//    and a simple swap will be done
//    removes 10 values at position index
// numTests will be the number of tests to run to get the average time
long vectorTest(int numElements, int function, int numTests) {
   Vector<int> vec;

   // set up Vector
   for (int i=0;i < numElements; i++) {
      vec.add(randomInteger(0,numElements-1));
   }

   // perform function
   long avgElapsedTime = 0;
   switch(function) {
   case 1:
       avgElapsedTime = vecAdd(vec,randomInteger(0,numElements-1), numTests);
       break;
   case 2:
       avgElapsedTime = vecInsert(vec,randomInteger(0,numElements-1), numTests);
       break;
   case 3:
       avgElapsedTime = vecRemove(vec, numElements / 2, numTests);
       break;
   case 4:
       avgElapsedTime = vecRemoveFast(vec, numElements / 2, numTests);
   }
   return avgElapsedTime;
}

// add 10 values to the vector and time how long it takes on average
long vecAdd(Vector<int> &vec, int value, int numTests) {
    long elapsedSum = 0;
    for (int i=0; i < numTests; i++) {
       Timer t;
       t.start();
       for (int j = 0; j < 10; j++) {
           vec.add(value);
       }
       elapsedSum += t.stop();
    }
    return elapsedSum / numTests;
}

// insert 10 values into the vector at position 0 and time
// how long it takes on average
long vecInsert(Vector<int> &vec, int value, int numTests) {
    long elapsedSum = 0;
    for (int i=0; i < numTests; i++) {
       Timer t;
       t.start();
       for (int j=0; j < 10; j++) {
           vec.insert(0,value);
       }
       elapsedSum += t.stop();
    }
    return elapsedSum / numTests;
}

// remove 10 values at index using the Vector's remove function
// and time how long it takes on average
long vecRemove(Vector<int> &vec, int index, int numTests) {
    long elapsedSum = 0;
    for (int i=0; i < numTests; i++) {
       Timer t;
       t.start();
       for (int j=0; j < 10; j++) {
           vec.remove(index);
       }
       elapsedSum += t.stop();
    }
    return elapsedSum / numTests;
}

// removes 10 value at index by swapping with the last value and
// then removing the last value, and finding the average time to
// do this
long vecRemoveFast(Vector<int> &vec, int index, int numTests) {
    long elapsedSum = 0;
    for (int i=0; i < numTests; i++) {
       Timer t;
       t.start();
       for (int j=0; j < 10; j++) {
           int sz = vec.size();
           vec[index] = vec[sz-1];
           vec.remove(sz-1);
       }
       elapsedSum += t.stop();
    }
    return elapsedSum / numTests;
}
