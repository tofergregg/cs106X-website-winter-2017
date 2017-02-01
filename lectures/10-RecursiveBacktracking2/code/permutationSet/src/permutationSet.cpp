// This program demonstrates how to use overloaded
// functions, and how to use a helper function
// to perform recursion

// By: Chris Gregg
// Date: February 1, 2017

#include <iostream>
#include "console.h"
#include "set.h"
#include "simpio.h"

using namespace std;

// function prototypes
Set<string> permute(string st, int length);
void permute(Set<string> &permutations, string soFar, string rest, int length);

int main() {
    string toPermute;
    int length;
    Set<string> permutations;
    while (true) {
        toPermute = getLine("Please enter a string to permute (blank to quit): ");
        if (toPermute == "") {
            break;
        }
        length = getInteger("How many characters for each permutation? ", "Please enter an integer: ");
        permutations = permute(toPermute, length);

        // test output
        for (string s : permutations) {
            cout << s << endl;
        }
        cout << "Total number of permutations: " << permutations.size() << endl;
    }

    return 0;
}

// Permute a string, returning a set containing
// all permutations of length n
Set<string> permute(string st, int n) {
    Set<string> permutations;
    permute(permutations, "", st, n);
    return permutations;
}

// Helper function that uses recursion to find permutations
void permute(Set<string> &permutations, string soFar, string rest, int n) {
    if ((int)soFar.length() == n) {
        // we have found a solution that is n characters long
        permutations.add(soFar);
    } else {
        // recurse by going through the rest of the word and finding all
        // solutions
        for (int i = 0; i < (int)rest.length(); i++) {
            string remaining = rest.substr(0, i) + rest.substr(i+1);
            permute(permutations, soFar + rest[i], remaining, n);
        }
    }
}
