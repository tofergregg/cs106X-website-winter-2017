/*
 * CS 106B, Chris Piech
 * This program demonstrates the use of the Stanford C++ Set class.
 * A set is a collection without duplicates that efficiently supports
 * the core operations of adding, removing, and searching for elements.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include "console.h"
#include "timer.h"
#include "hashset.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

// function prototype declarations
bool contains(Vector<string>& v, string& s);
void wordCount(string filename);

int main() {
    // use a timer to see how long the function takes to run
    Timer timer;
    timer.start();

    HashSet<string> uniqueWords;

    ifstream input;
    openFile(input, "mobydick.txt");
    string word;
    while (input >> word) {   // read one word
        uniqueWords.add(word);
    }

    cout << "Found " << uniqueWords.size() << " words " << endl;
    cout << "Took " << timer.stop() << " ms." << endl;

    return 0;
}

/*
 * Returns true if the given vector contains the given string, otherwise false.
 */
bool contains(Vector<string>& v, string& s) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == s) {
            return true;
        }
    }
    return false;
}
