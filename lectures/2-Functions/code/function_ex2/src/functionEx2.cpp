// Function example #2: returning values

#include <iostream>
#include "console.h"

using namespace std;

int larger(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Returns the larger of the two values.
int main() {
    int bigger1 = larger(17, 42); // call the function
    int bigger2 = larger(29, -3); // call the function again
    int biggest = larger(bigger1, bigger2);
    cout << "The biggest is " << biggest << "!!" << endl;
    return 0;
}
