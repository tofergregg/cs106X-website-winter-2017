/*
 * CS 106B, Marty Stepp
 * This file implements the members of the Employee class, the parent (base)
 * class in our inheritance hierarchy.
 */

#include "Employee.h"

Employee::Employee(string name, int years) {
    myName = name;
    myYears = years;
}

int Employee::hours() const {
    return 40;
}

string Employee::name() const {
    return myName;
}

double Employee::salary() const {
    return 50000.0 + (500 * myYears);
}

int Employee::vacationDays() const {
    return 10;
}

string Employee::vacationForm() const {
    return "yellow";
}

int Employee::years() const {
    return myYears;
}
