// This program prints out permutations of strings
// Note: it contains some Terrible, Horrible, No Good, Very Bad Code
// (that is commented as such)
// By: Chris Gregg
// Date: October 16, 2016
#include <iostream>
#include <climits> // for INT_MAX
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "random.h"
#include "timer.h"

using namespace std;

// prototypes
int requestTest();
void doVectorMaxTest();
void doSearchTest();
void doFibTest(int test);

void testVectorMax(int num_elements);
int vectorMax(Vector<int> &v);

void testSearchVector(int n);
void linearSearchVector(Vector<int> &vec, int numToFind);
void binarySearchVector(Vector<int> &vec, int numToFind);

long fibonacci(int n);
long fibonacciIter(int n);
long fibHelper(int n, long p0, long p1);
long fibonacciRec2(int n);

int main() {
    int testNum = -2;
    while (testNum != -1) {
        testNum = requestTest();
        switch (testNum) {
        case 0:
            doVectorMaxTest();
            break;
        case 1:
            doSearchTest();
            break;
        case 2:
        case 3:
        case 4:
            doFibTest(testNum);
            break;
        }
        cout << endl;
    }
    cout << "Goodbye!" << endl;
    return 0;
}

int requestTest() {
    int response = -2; // initial condition
    cout << "Asymptotic Behavior Tests" << endl;
    cout << "0. Vector Max Test" << endl;
    cout << "1. Linear Search vs Binary Search" << endl;
    cout << "2. Mystery Recursive (Exponential Time Complexity)" << endl;
    cout << "3. Mystery Iterative (Linear Time Complexity)" << endl;
    cout << "4. Mystery Recursive (Linear Time Complexity)" << endl;
    cout << endl;
    while (response < -1 or response > 4) {
        response = getInteger("Please choose an option (0-4), -1 to quit: ");
    }
    return response;
}

void doVectorMaxTest() {
    cout << "n,max,time(ms)" << endl;
    int begin = 1<<18; // 2^18
    int end = (1<<29) + 1; // 2^30 + 1
    for (int n=begin; n < end; n*=2) {
        cout << n << ",";
        cout << flush;
        testVectorMax(n);
    }
    cout << "Done!" << endl;
}

void testVectorMax(int num_elements) {
    Timer t;
    int max;
    Vector<int> v;
    for (int i = 0; i < num_elements; i++) {
        v.add(randomInteger(0,INT_MAX));
    }
    t.start();
    max = vectorMax(v);
    t.stop();
    cout << max << ",";
    cout << t.elapsed() << endl;
}

int vectorMax(Vector<int> &v){
    int currentMax = v[0];
    int n = v.size();
    for (int i = 1; i < n; i++) {
        if (currentMax < v[i]) {
            currentMax = v[i];
        }
    }
    return currentMax;
}

void doSearchTest() {
    cout << "Linear search -vs- Binary Search" << endl;
    int begin = 1<<18; // 2^18
    int end = (1<<29) + 1; // 2^30 + 1
    for (int n=begin; n < end; n*=2) {
        cout << "Number of elements: " << n << ",";
        cout << flush;
        testSearchVector(n);
    }
    cout << "Done!" << endl;
}

void testSearchVector(int n) {
    // set the random seed to a particular value so
    // we can directly compare the linear and binary search
    setRandomSeed(1234);

    // fill the vector in order, even though we may be
    // doing a linear search -- we can then compare
    // the linear and binary search
    Vector<int> vec;
    int last = 0;
    for (int i = 0; i < n; i++) {
        // put some randomness into it
        int r = randomInteger(last + 1,last + 5);
        last = r;
        vec.add(r);
    }
    // perform the search
    int searchVal = randomInteger(0,n);
    cout << "Searching for: " << searchVal << endl;

    cout << "Linear search:" << endl;
    linearSearchVector(vec, searchVal);

    cout << "Binary search:" << endl;
    binarySearchVector(vec, searchVal);
    cout << endl;
}

void linearSearchVector(Vector<int> &vec, int numToFind){
    int numCompares = 0;
    bool answer = false;
    int n = vec.size();

    for (int i = 0; i < n; i++) {
        numCompares++;
        if (vec[i]==numToFind) {
            answer = true;
            break;
        }
    }
    cout << "Found? " << (answer ? "True" : "False") << ", " <<
            "Number of compares: " << numCompares << endl << endl;
}

void binarySearchVector(Vector<int> &vec, int numToFind) {
    int low=0;
    int high=vec.size()-1;
    int mid;
    int numCompares = 0;
    bool found=false;
    while (low <= high) {
        numCompares++;
        //cout << low << ", " << high << endl;
        mid = low + (high - low) / 2; // to avoid overflow
        if (vec[mid] > numToFind) {
            high = mid - 1;
        }
        else if (vec[mid] < numToFind) {
            low = mid + 1;
        }
        else {
            found = true;
            break;
        }
    }
    cout << "Found? " << (found ? "True" : "False") << ", " <<
            "Number of compares: " << numCompares << endl << endl;
}

// Fibonacci tester
void doFibTest(int test) {
    long fib;

    cout << "Running fibonacci sequence generator with " << endl;
    switch (test) {
    case 2:
        cout << "recursive function (exponential time complexity)" << endl;
        break;
    case 3:
        cout << "iterative function (linear time complexity)" << endl;
        break;
    case 4:
        cout << "recursive function with helper (linear time complexity)" << endl;
        break;
    }

    // we'll never make it to 92 with exponential, but we can try!
    // (heat death of the universe...)
    // (92 is the max that will fit into a long)
    for (int n = 0; n < 93; n++) {
        Timer t;
        t.start();
        if (test == 2) {
            fib = fibonacci(n);
        } else if (test == 3) {
            fib = fibonacciIter(n);
        } else if (test == 4){
            fib = fibonacciRec2(n);
        }

        t.stop();
        cout << "n: " << n << " = " << fib
             << ", time: " << t.elapsed() << "ms" << endl;
    }
}

// Fibonacci number generator
// (exponential time complexity!)
long fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

// iterative solution

long fibonacciIter(int n) {
    long result = 1;
    long prev = 1;
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    for (int i = 2; i < n; i++) {
        long current = result;
        result += prev;
        prev = current;
    }
    return result;
}

// better recursive fibonacci solution
long fibHelper(int n, long p0, long p1){
    if (n==1) return p1;
    // pre-calculate partial results,
    // and pass them along
    return fibHelper(n-1,p1,p0+p1);
}

long fibonacciRec2(int n){
    if (n==0) return 0;
    return fibHelper(n,0,1);
}
