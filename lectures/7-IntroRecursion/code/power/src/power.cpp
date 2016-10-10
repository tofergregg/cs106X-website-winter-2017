

#include <fstream>
#include <iostream>
#include <iomanip>
#include "console.h"
#include "filelib.h"
#include "simpio.h"

using namespace std;

void testPower(int base, int exp, double expected);

double power(int base, int exponent) {
    if(exponent == 0) {
        // base case
        return 1;    // no trebble....
    } else if(exponent < 0) {
        // recursive case 1
        return 1.0 / power(base, -exponent);
    } else {
        // recursive case 2
        return base * power(base, exponent - 1);
    }
}

int main() {
    cout << "Recursive power" << endl;
    testPower(2, 5, 32);
    testPower(5, 5, 3125);
    testPower(0, 6, 0);
    testPower(-6, 3, -216);
    testPower(6, 0, 1);
    testPower(2, -3, 0.125);
    cout << "Done!" << endl;
    return 0;
}

void testPower(int base, int exponent, double expected) {
    cout << "testPower(" << base << ", " << exponent << "): " << flush;
    double result = power(base, exponent);
    cout << "\t" << result;
    if(result == expected) {
        cout << "\t[passed]" << endl;
    } else {
        cout << "\t[failed]" << endl;
    }
}

