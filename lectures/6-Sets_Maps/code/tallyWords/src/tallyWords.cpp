/* CS 106X, based on an example by Chris Piech
 * This program demonstrates the use of the Stanford C++ Map class.
 * A map is a collection of key/value pairs that allows you to
 * efficiently look up a value if you know its key.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctype.h> // for isalpha
#include "console.h"
#include "hashmap.h"
#include "map.h"
#include "simpio.h"
#include "strlib.h"
#include "filelib.h"

using namespace std;

// function prototype declarations
void wordTally(string filename);
string alphaOnly(string s);

int main() {
    wordTally("mobydick.txt");
    return 0;
}

/*
 * Reads the given input file and produces a map of tallies of the form:
 * {word => number of occurrences of that word in the file}.
 * Prompts the user to enter words and looks up # of occurrences of the words.
 */
void wordTally(string filename) {

    ifstream input;
    openFile(input, filename);

    // to: 1
    // whale: 300 or 1
    Map<string, int> tally;

    string word;
    while (input >> word) {   // read one word
        word = alphaOnly(word);
        word = toLowerCase(word);
//        if(!tally.containsKey(word)) {
//            tally.put(word, 1);
//        } else {
//            int count = tally.get(word);
//            count++;
//            tally.put(word, count);
//        }
        tally[word]++;
    }

    // this loop asks the user for the word and outputs
    // the corresponding tally.
    while (true) {
        string word = toLowerCase(trim(getLine("Word to search for (Enter to quit)? ")));
        if (word == "") {
            break;
        } else {
            int count = tally.get(word);
            cout << word << " occurs " << count << " times." << endl;
        }
    }
}


string alphaOnly(string fullStr) {
    // walk through the string and just keep the alpha characters
    string alphaStr;
    for (char c : fullStr) {
        if (isalpha(c)) {
            alphaStr += c;
        }
    }
    return alphaStr;
}
