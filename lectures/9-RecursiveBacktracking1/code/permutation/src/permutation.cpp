// This program prints out permutations of strings
// Note: it contains some Terrible, Horrible, No Good, Very Bad Code
// (that is commented as such)
// By: Chris Gregg
// Date: October 16, 2016
#include <iostream>
#include "console.h"
#include "vector.h"
#include <fstream>
#include "simpio.h"
#include "filelib.h"
#include "lexicon.h"
#include "set.h"

using namespace std;

const string DICTIONARY = "dictionary.txt";

// function prototypes

// Functions you do not want to use or write!
void permute4(string s);
void permute5(string s);
void permute6(string s);

// Extra terrible
// So bad, your eyes might bleed if you look at it
void permute4b(string s);

// Much better
void recPermute(string s);
void recPermuteRealWords(string s, Lexicon &lex);
void recCombinations(string s);


// Helper function for recPermute() and recPermuteRealWords()
void recPermuteHelper(string soFar, string rest);
void recPermuteHelperRealWords(string soFar, string rest,
                               Lexicon &lex, Set<string> &goodWords);
void recCombinationsHelper(string orig, string soFar);

int main() {
    // finds dictionary words that match
    /*
    Lexicon lex(DICTIONARY);
    recPermuteRealWords("legia", lex);
    recPermuteRealWords("knidy", lex);
    recPermuteRealWords("cronee", lex);
    recPermuteRealWords("tuvedo", lex);
    recPermuteRealWords("diainodt", lex);
    */

    // prints out all permutations
    recPermute("abcde");

    // prints out all combinations
    //recCombinations("abcde");

    // no, no, no. Bad functions.
    // permute4("abcd");
    // permute5("legia");
    // permute6("cronee");
    // permute4b("abcd");
    return 0;
}

void recPermute(string s) {
    recPermuteHelper("",s);
}

void recPermuteHelper(string soFar, string rest) {
    if (rest == "") {
        cout << soFar << endl;
    } else {
        for (int i = 0; i < (int)rest.size(); i++) {
            string remaining = rest.substr(0, i)
                    + rest.substr(i+1);
            recPermuteHelper(soFar + rest[i], remaining);
        }
    }
}

// Allow duplicates (combinations)
void recCombinations(string s) {
    recCombinationsHelper(s,"");
}

void recCombinationsHelper(string orig, string soFar) {
    if (orig.length() == soFar.length()) {
        cout << soFar << endl;
    } else {
        for (char c : orig) {
            recCombinationsHelper(orig,soFar+c);
        }
    }
}
void recPermuteRealWords(string s, Lexicon &lex) {
    // determine all anagrams of string s that are in
    // the dictionary lex
    Set<string> goodWords;
    recPermuteHelperRealWords("", s, lex, goodWords);
    cout << "Dictionary words that are anagrams of "
         << s << ":" << endl;
    for (string word : goodWords) {
        cout << word << endl;
    }
    cout << endl;
}

void recPermuteHelperRealWords(string soFar, string rest,
                               Lexicon &lex, Set<string> &goodWords) {

    if (rest == "") {
        if (lex.contains(soFar)) {
            goodWords.add(soFar);
        }
    } else {
        for (int i = 0; i < (int)rest.size(); i++) {
            string remaining = rest.substr(0, i)
                    + rest.substr(i+1);
            recPermuteHelperRealWords(soFar + rest[i], remaining,lex,goodWords);
        }
    }
}


// Here be dragons!
// The following code is
// Terrible, Horrible, No Good, Very Bad Code
// Only included here as a warning of what not to do

// permute4()
// Terrible, Horrible, No Good, Very Bad Code
// Does not scale, is not pretty
void permute4(string s) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 ; j++) {
            if (j == i) {
                continue; // ignore
            }
            for (int k = 0; k < 4; k++) {
                if (k == j || k == i) {
                    continue; // ignore
                }
                for (int w = 0; w < 4; w++) {
                    if (w == k || w == j || w == i) {
                        continue; // ignore
                    }
                    cout << s[i] << s[j] << s[k] << s[w] << endl;
                }
            }
        }
    }
}

// permute5()
// Terrible, Horrible, No Good, Very Bad Code
// Yuck, yuck, yuck.
void permute5(string s) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 ; j++) {
            if (j == i) {
                continue; // ignore
            }
            for (int k = 0; k < 5; k++) {
                if (k == j || k == i) {
                    continue; // ignore
                }
                for (int w = 0; w < 5; w++) {
                    if (w == k || w == j || w == i) {
                        continue; // ignore
                    }
                    for (int x = 0; x < 5; x++) {
                        if (x == k || x == j || x == i || x == w) {
                            continue;
                        }
                        cout << "  " << s[i] << s[j] << s[k] << s[w] << s[x] << endl;
                    }
                }
            }
        }
    }
}

// permute6()
// Terrible, Horrible, No Good, Very Bad Code
// What has been seen cannot be un-seen
void permute6(string s) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 ; j++) {
            if (j == i) {
                continue; // ignore
            }
            for (int k = 0; k < 5; k++) {
                if (k == j || k == i) {
                    continue; // ignore
                }
                for (int w = 0; w < 5; w++) {
                    if (w == k || w == j || w == i) {
                        continue; // ignore
                    }
                    for (int x = 0; x < 5; x++) {
                        if (x == k || x == j || x == i || x == w) {
                            continue;
                        }
                        for (int y = 0; y < 6; y++) {
                            if (y == k || y == j || y == i || y == w || y == x) {
                                continue;
                            }
                            cout << "  " << s[i] << s[j] << s[k] << s[w] << s[x] << s[y] << endl;
                        }
                    }
                }
            }
        }
    }
}

// permute4b()
// permute a string of length 4 using swapping
// ***** Terrible, Horrible, No Good, Very Bad Code *****
// Hard to understand, not easily extendable to
// strings more than four characters.
// Doesn't scale, etc.
// Look only if you like being scared.
void permute4b(string s) {
    char temp;
    string orig;
    for (int i = 1; i < 5 ; i++) {
        orig = s;
        for (int j = 2 ; j < 5 ; j++) { // one more to rotate back to original
            for (int k = 3 ; k < 5; k++) {
                cout << "  " << s << endl;
                // swap 2,3
                if (k < 4) {
                    temp = s[2];
                    s[2] = s[k];
                    s[k] = temp;
                }
                else {
                    // swap back to original
                    temp = s[2];
                    s[2] = s[3];
                    s[3] = temp;
                }
            }
            // swap 1,2; 1,3
            if (j < 4) {
                temp = s[1];
                s[1] = s[j];
                s[j] = temp;
            }
            else {
                s = orig;
            }
        }
        // swap 0,1; 0,2; 0,3, unless we are done
        temp = s[0];
        s[0] = s[i];
        s[i] = temp;
    }
}
