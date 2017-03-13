/*
 * CS 106B, Marty Stepp
 * This file implements the members of the Lawyer class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#include <iostream>
#include "Lawyer.h"

// call the constructor of Employee superclass?
Lawyer::Lawyer(string name, string lawSchool, int years)
        : Employee(name, years) {
    myLawSchool = lawSchool;
}

// overriding: replace version from Employee class
double Lawyer::salary() const {
    return Employee::salary() * 2;
}

void Lawyer::sue(string person) {
    cout << "See you in court, " << person << endl;
}
