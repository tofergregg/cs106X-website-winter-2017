#include <iostream>
#include "console.h"
#include "simpio.h"  // for getLine
#include "map.h"
#include "timer.h" // for timing
using namespace std;

// Fibonacci Sequence

// function prototypes
long plainRecursiveFib(int n);
long memoizationFib(int n);
long memoizationFib(Map<int,long> &cache, int n);
long passValuesRecursiveFib(int n);
long passValuesRecursiveFib(int n, long p0, long p1);
long iterativeFib(int n);

int main() {
    int selection = -1;
    int fibN;
    long result;

    Timer t;

    while (true) {
        cout << "Please choose among the following algorithms:" << endl;
        cout << "1) Plain recursive Fibonacci." << endl;
        cout << "2) Recurisve Memoization Fibonacci." << endl;
        cout << "3) Recursive pass-values Fibonacci." << endl;
        cout << "4) Iterative Fibonacci." << endl;
        cout << "5) End." << endl;

        while (selection < 0 or selection > 5) {
            selection = getInteger("Please make a choice: ","Please type an integer!");
        }

        if (selection == 5) {
            break;
        }

        fibN = getInteger("What fibonacci number would you like to generate? ");


        t.start();
        switch(selection) {
        case 1:
            result = plainRecursiveFib(fibN);

        case 2:
            result = memoizationFib(fibN);
            break;
        case 3:
            result = passValuesRecursiveFib(fibN);
            break;
        case 4:
            result = iterativeFib(fibN);
            break;
        default:
            result = 0;
            break;
        }
        t.stop();
        cout << "Fibonnaci number " << fibN << " equals: " << result << endl;
        cout << "Time: " << t.elapsed() << "ms" << endl << endl;
        selection = -1;
    }
    cout << "Goodbye!" << endl;

    return 0;
}

long plainRecursiveFib(int n) {
    if(n == 0) {
        // base case
        return 0;
    } else if (n == 1) {
        // base case
        return 1;
    } else {
        // recursive case
        return plainRecursiveFib(n - 1) + plainRecursiveFib(n - 2);
    }
}

long memoizationFib(int n) {
    Map<int, long> cache;
    return memoizationFib(cache, n);
}

long memoizationFib(Map<int, long>&cache, int n) {
    if(n == 0) {
        // base case #1
        return 0;
    } else if (n == 1) {
        // base case #2
        return 1;
    } else if(cache.containsKey(n)) {
        // base case #3
        return cache[n];
    }
    // recursive case
    long result = memoizationFib(cache, n-1) + memoizationFib(cache, n-2);
    cache[n] = result;
    return result;
}


long passValuesRecursiveFib(int n) {
    if (n == 0) {
        return 0;
    }
    return passValuesRecursiveFib(n, 0, 1);
}

long passValuesRecursiveFib(int n, long p0, long p1) {
    if (n == 1) {
        // base case
        return p1;
    }
    return passValuesRecursiveFib(n-1,p1, p0 + p1);
}

long iterativeFib(int n) {
    if(n == 0) {
        // base case
        return 0;
    }
    long prev0 = 0;
    long prev1 = 1;
    for (int i=n; i >= 2; i--) {
       long temp = prev0 + prev1;
       prev0 = prev1;
       prev1 = temp;
    }
    return prev1;
}

