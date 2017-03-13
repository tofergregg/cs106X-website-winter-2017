/*
 * CS 106B, Marty Stepp
 * This client program creates several variables of the classes in our
 * inheritance hierarchy and then calls methods on them.
 */

#include <iostream>
#include "console.h"
#include "polymorphism.h"
using namespace std;

int main() {
    // Example 1
    cout << "Example 1:" << endl;
    Snow* var1 = new Sleet();
    var1->method2();

    cout << endl;

    // Example 2
    cout << "Example 2:" << endl;
    Snow* var2 = new Rain();
    // var2->method1();

    cout << endl;

    // Example 3
    cout << "Example 3:" << endl;
    Snow* var3 = new Sleet();
    var3->method3();

    cout << endl;

    // Example 4
    cout << "Example 4:" << endl;
    Snow* var4 = new Rain();
    ((Rain*) var4)->method1();

    cout << endl;

    // Example 5
    cout << "Example 5:" << endl;
    Snow* var5 = new Fog();
    // ((Sleet*) var5)->method1();

    cout << endl;

    // Example 6
    cout << "Example 6:" << endl;
    Snow* var6 = new Sleet();
    ((Rain*) var6)->method1();

    cout << endl;

    cout << "Done!  Exiting." << endl;
    return 0;
}
