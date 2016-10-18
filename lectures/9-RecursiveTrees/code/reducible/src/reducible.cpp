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
#include "lexicon.h"

using namespace std;

bool reducible(Lexicon & lex, string word) {
    // base case
    if(word.length() == 1 && lex.contains(word)) {
        return true;
    }

    // recursive case
    for(int i = 0; i < word.length(); i++) {
        string copy = word;
        copy.erase(i, 1);

        if(lex.contains(copy)) {
            if(reducible(lex, copy)) {
                return true;
            }
        }
    }
    return false;
}

void checkReducible(Lexicon & lex, string word) {
    if(reducible(lex, word)) {
        cout << word << " IS reducible" << endl;
    } else {
        cout << word << " is NOT reducible" << endl;
    }
}

int main() {
    Lexicon lexicon("EnglishWords.txt");

    checkReducible(lexicon, "startling");
    checkReducible(lexicon, "cart");
    checkReducible(lexicon, "twitchiest");
    checkReducible(lexicon, "mehran");

    /*for(string word : lexicon) {
        if(word.length() >= 9) {
            if(reducible(lexicon, word)) {
                cout << word << endl;
            }
        }
    }*/

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
