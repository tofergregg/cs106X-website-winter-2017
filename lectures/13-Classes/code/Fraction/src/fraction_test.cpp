#include <iostream>
#include "console.h"
#include "fraction.h"

using namespace std;

int main() {
    // create three fractions

    // a default fraction
    Fraction fracA; // should be 1/1
    cout << fracA << " (should be 1/1)" << endl;

    Fraction fracB(1,2); // 1/2
    cout << fracB << " (should be 1/2)" << endl;

    Fraction fracC(2,3); // 2/3
    cout << fracC << " (should be 2/3)" << endl;

    float f = fracC.decimal();
    cout << f << " (should be 0.666667)" << endl;

    fracB.mult(fracC);
    cout << fracB << " (should be 1/3)" << endl;

    fracB.add(fracA);
    cout << fracB << " (should be 4/3)" << endl;

    fracB.add(fracC);
    cout << fracB << " (should be 2/1)" << endl;

    Fraction fracD(20,20);
    cout << fracD << " (should be 1/1)" << endl;

    Fraction fracZero(0,10); // really, 0
    cout << fracZero << " (should be 0/1)" << endl;
    return 0;
}
