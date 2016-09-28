#include <iostream>
#include "console.h"

using namespace std;

const string DRINK_TYPE = "Coke";

// Function Definition and Code
void bottles(int count) {
    cout << count << " bottles of " << DRINK_TYPE << " on the wall." << endl;
    cout << count << " bottles of " << DRINK_TYPE << "." << endl;
    cout << "Take one down, pass it around, "
         << (count-1) << " bottles of " << DRINK_TYPE
         << " on the wall." << endl << endl;
}

int main() {
    for (int i=99; i > 0; i--) {
        bottles(i);
    }
    return 0;
}
