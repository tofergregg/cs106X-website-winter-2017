/*
 * CS 106X, Chris Gregg
 * This program demonstrates how to perform recursion on a
 * decision tree.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include "console.h"
#include "lexicon.h"
#include "vector.h"
#include "lexicon.h"

using namespace std;

// function prototypes
bool reducible(Lexicon &lex, string word);
void checkReducible(Lexicon &lex, string word);

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

bool reducible(Lexicon & lex, string word) {
    // base case
    if(word.length() == 1 && lex.contains(word)) {
        return true;
    }

    // recursive case
    for(int i = 0; i < (int)word.length(); i++) {
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
