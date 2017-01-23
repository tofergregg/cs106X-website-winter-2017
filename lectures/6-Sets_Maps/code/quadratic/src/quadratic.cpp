#include <iostream>
#include <cmath>
#include <ctype.h> // for isdigit
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "string.h" // for stringSplit
#include "vector.h"
using namespace std;

// Quadratic Equation Solver

struct Roots {
    double root1;
    double root2;
};

// Function prototypes
Roots quadratic(double a, double b, double c);
void parseRoots(string eq, double &a, double &b, double &c);
double dirtyStringToDouble(string dirtyStr);

int main() {
    string equation;
    while (true) {
        equation = getLine("Please enter an equation in the form Axx + Bx + C: ");
        if (equation == "") {
            break;
        }
        double a,b,c;
        parseRoots(equation,a,b,c);
        Roots roots = quadratic(a,b,c);
        cout << "Solution:" << endl;
        cout << "Root 1:" << roots.root1 << endl;
        cout << "Root 2:" << roots.root2 << endl;
    }
    return 0;
}

/*
 * Solves a quadratic equation ax^2 + bx + c = 0,
 * storing the results in output parameters root1 and root2.
 * Assumes that the given equation has two real roots.
 */
Roots quadratic(double a, double b, double c) {
    Roots roots;
    double d = sqrt(b * b - 4 * a * c);
    roots.root1 = (-b + d) / (2 * a);
    roots.root2 = (-b - d) / (2 * a);
    return roots;
}

void parseRoots(string eq, double &a, double &b, double &c) {
    // Equation should be in the form: Axx + Bx + C
    // split by finding "x"
    Vector<string> parts = stringSplit(eq,"x");

    // get a clean double from each part
    a = dirtyStringToDouble(parts[0]);
    // parts[1] should be empty becuase of the xx
    b = dirtyStringToDouble(parts[2]);
    c = dirtyStringToDouble(parts[3]);
}

double dirtyStringToDouble(string dirtyStr) {
    // removes non-digits and periods from a string,
    // then returns stringToDouble()
    string cleanStr;
    for (char c : dirtyStr) {
        if (isdigit(c) or (c == '.')) {
            cleanStr += c;
        }
    }
    return stringToDouble(cleanStr);
}
