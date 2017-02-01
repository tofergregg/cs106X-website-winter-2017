// This program demonstrates how to use overloaded
// functions, and how to use a helper function
// to perform recursion

// By: Chris Gregg
// Date: February 1, 2017

#include <iostream>
#include <fstream>
#include "console.h"
#include "set.h"
#include "map.h"
#include "simpio.h"
#include "lexicon.h"

using namespace std;

// function prototypes
Set<string> autocorrect(string word,
                        Map<char, string> & nearLetters,
                        Lexicon & dictionary,
                        int maxTypos);

Set<string> autocorrect(string remaining, Map<char, string> &nearLetters,
                        Lexicon & dictionary, int allowableTypos, string
                        builtUp);

int main() {
    Map<char,string> nearLettersMap;
    ifstream nearLettersFile;
    string wordToCorrect;
    int maxLettersIncorrect;

    nearLettersFile.open("nearLettersMap.txt");
    nearLettersFile >> nearLettersMap;
    nearLettersFile.close();

    Lexicon dictionary;
    dictionary.addWordsFromFile("dictionary.txt");

    while (true) {
        wordToCorrect = getLine("Word to check? (blank to quit) ");
        if (wordToCorrect == "") {
            break;
        }
        maxLettersIncorrect = getInteger("How many characters can be incorrect? ",
                                         "Please enter an integer");

        Set<string> correctedWords;
        correctedWords = autocorrect(wordToCorrect,
                                     nearLettersMap,
                                     dictionary,
                                     maxLettersIncorrect);

        cout << wordToCorrect << " has " << correctedWords.size()
             << " possible corrections: ";
        int wordCount = 0;
        for (string word : correctedWords) {
            cout << word;
            if (wordCount < correctedWords.size() - 1) {
                cout << ", ";
            }
            wordCount++;
        }
        cout << endl;
    }
    cout << "Goodbye!" << endl;
    return 0;
}

Set<string> autocorrect(string word,
                        Map<char, string> & nearLetters,
                        Lexicon & dictionary,
                        int maxTypos) {
    return autocorrect(word, nearLetters, dictionary,maxTypos, "");
}

Set<string> autocorrect(string remaining, Map<char, string> &nearLetters,
                        Lexicon & dictionary, int allowableTypos, string
                        builtUp) {
    Set<string> result;
    if (allowableTypos < 0 || !dictionary.containsPrefix(builtUp)) {
        // too many typos, or no potential to build word
        return result; //empty set
    } else if (remaining == "") {
        if (dictionary.contains(builtUp)) {
            // if word, add it to set
            result.add(builtUp);
        }
        return result;
    }
    char curr = remaining[0];
    string rest = remaining.substr(1);
    for (int i = 0; i < (int)nearLetters[curr].length(); i++) {
        result += autocorrect(rest, nearLetters,dictionary,
                              allowableTypos - 1, builtUp + nearLetters[curr][i]);
    }

    //can also choose not to change character
    result += autocorrect(rest, nearLetters, dictionary,
                          allowableTypos, builtUp + curr);
    return result;
}
