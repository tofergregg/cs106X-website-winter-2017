/*
 * CS 106B, Marty Stepp
 * This client program creates several variables of the classes in our
 * inheritance hierarchy and then calls methods on them.
 */

#include <iostream>
#include "console.h"
#include "polymorphism.h"
#include "simpio.h"
using namespace std;


int main() {
    int choice = -1;
    while (choice != 0) {
        choice = getInteger("Example to run (1-7, 0 to quit): ");

        if (choice == 1) {
            // Example 1
            cout << "Example 1:" << endl;
            Snow* var1 = new Sleet();
            var1->method2();

            cout << endl;
        }

        if (choice == 2) {
            // Example 2
            cout << "Example 2:" << endl;
            Snow* var2 = new Rain();
            //var2->method1();

            cout << endl;
        }

        if (choice == 3) {
            // Example 3
            cout << "Example 3:" << endl;
            Snow* var3 = new Rain();
            var3->method2();

            cout << endl;
        }

        if (choice == 4) {
            // Example 4
            cout << "Example 4:" << endl;
            Snow* var4 = new Rain();
            ((Rain*) var4)->method1();

            cout << endl;
        }

        if (choice == 5) {
            // Example 5
            cout << "Example 5:" << endl;
            Snow* var5 = new Fog();
            // ((Sleet*) var5)->method1();

            cout << endl;
        }

        if (choice == 6) {
            // Example 6
            cout << "Example 6:" << endl;
            Snow* var6 = new Sleet();
            //((Rain*) var6)->method4();

            cout << endl;
        }

        if (choice == 7) {
            // Example 7
            cout << "Example 7:" << endl;
            Snow* var7 = new Sleet();
            ((Rain*) var7)->method1();

            cout << endl;
        }
        cout << "Finished Example " << choice << endl << endl;
    }
    cout << "Done!  Exiting." << endl;
    return 0;
}

