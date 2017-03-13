/*
 * CS 106B, Marty Stepp
 * This client program uses our classes built with inheritance.
 */

#include <iostream>
#include <iomanip>
#include "console.h"
#include "Employee.h"
#include "Programmer.h"
#include "Lawyer.h"
using namespace std;

// function prototype declarations
void printEmployeeInfo(Employee* employee);

int main() {
    Employee* edward = new Employee("Edward", 4);
    printEmployeeInfo(edward);

    Employee* lisa = new Lawyer("Lisa", "Stanford", 6);
    printEmployeeInfo(lisa);
    // lisa->sue("Marty");

//    Programmer* pete = new Programmer("Pete", 2);
//    printEmployeeInfo(pete);
//    pete->code();

    return 0;
}

/*
 * Prints various statistics about the given employee.
 * This method demonstrates polymorphism, because it uses
 * the methods from whatever type of employee class you pass it.
 */
void printEmployeeInfo(Employee* employee) {
    cout << endl;
    cout << "Employee information:" << endl;
    cout << "Name:          " << employee->name() << endl;
    cout << "Years:         " << employee->years() << endl;
    cout << "Salary:       $" << fixed << setprecision(2) << employee->salary() << endl;
    cout << "Vacation days: " << employee->vacationDays() << endl;
    cout << "Vacation form: " << employee->vacationForm() << endl;
}










