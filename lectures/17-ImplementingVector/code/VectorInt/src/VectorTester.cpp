// Tests for Vector

#include <iostream>
#include "VectorInt.h"
#include "console.h"

using namespace std;

int main() {
    cout << "Constructing and empty vector." << endl;
    VectorInt vec;

    cout << "Testing for empty: " << endl;
    cout << (vec.isEmpty() ? "True (" : "False (");
    if (vec.isEmpty()) {
        cout << "Passed).";
    } else {
        cout << "Failed).";
    }

    cout << endl << endl;

    cout << "Adding five elements, 0,1,2,3,4. Size should be 5." << endl;
    for (int i=0; i < 5; i++) {
        vec.add(i);
    }
    cout << (vec.size() == 5 ? "True (" : "False (");
    if (vec.size() == 5) {
        cout << "Passed).";
    } else {
        cout << "Failed).";
    }

    cout << endl << endl;

    cout << "Printing out vector. Should print [0, 1, 2, 3, 4]" << endl;
    cout << vec << endl;

    cout << "Inserting 100 at index 3. Should now have a size of 6 ";
    cout << "and print out [0, 1, 2, 100, 3, 4] ";

    vec.insert(3, 100);
    if (vec.size() == 6) {
        cout << "(Passed)." << endl;
    } else {
        cout << "(Failed)." << endl;
    }
    cout << vec << endl << endl;

    cout << "Removing at index 4. Should now have a size of 5 ";
    cout << "and print out [0, 1, 2, 100, 4] ";

    vec.remove(4);
    if (vec.size() == 5) {
        cout << "(Passed)." << endl;
    } else {
        cout << "(Failed)." << endl;
    }
    cout << vec << endl << endl;

    cout << "Inserting 200 at index 0. Should now have a size of 6 ";
    cout << "and print out [200, 0, 1, 2, 100, 4] ";

    vec.insert(0, 200);
    if (vec.size() == 6) {
        cout << "(Passed)." << endl;
    } else {
        cout << "(Failed)." << endl;
    }
    cout << vec << endl << endl;

    cout << "Inserting 300 at index 6. Should now have a size of 7 ";
    cout << "and print out [200, 0, 1, 2, 100, 4, 300] ";

    vec.insert(6, 300);
    if (vec.size() == 7) {
        cout << "(Passed)." << endl;
    } else {
        cout << "(Failed)." << endl;
    }
    cout << vec << endl << endl;

    cout << "Adding 1000 more elements (1000-1999). Tests expansion." << endl;
    cout << "Should have a count of 1007 and print out" << endl;
    cout << "[200, 0, 1, 2, 100, 4, 300, 1000, 1001, ..., 1998, 1999] " << flush;

    for (int i=1000; i < 2000; i++) {
        vec.add(i);
    }
    if (vec.size() == 1007) {
        cout << "(Passed)." << endl;
    } else {
        cout << "(Failed)." << endl;
    }
    cout << vec << endl << endl;
    return 0;
}
