/*
 * CS 106B, Marty Stepp
 * This file implements the members of the Programmer class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#include <iostream>
#include "Programmer.h"

Programmer::Programmer(string name, int years) : Employee(name, years) {}

string Programmer::vacationForm() const {
    return "pink";
}

void Programmer::code() {
    cout << "I'm coding up a storm!" << endl;
}
