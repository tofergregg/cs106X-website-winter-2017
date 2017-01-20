// Match symbols using a stack

#include <iostream>
#include <cmath>
#include "console.h"
#include "simpio.h"  // for getLine
#include "stack.h"

using namespace std;

// function prototypes
string getInput();
bool bracketsMatch(string input, char &unmatched);
bool closingBracketOkay(char c, Stack<char> &s);
void printInputWithLines(string input);
void printSpaces(int n);

// constants
const string openingBrackets = "{[(";
const string closingBrackets = "}])";

int main() {
    string input = getInput();
    char unmatched;
    cout << "The input:" << endl << endl;
    printInputWithLines(input);
    if (bracketsMatch(input,unmatched)) {
        cout << "All brackets match!" << endl;
    } else {
        cout << "The following symbol didn't match: " << unmatched << endl;
    }
    return 0;
}

string getInput() {
    string allInput;
    string oneLine;
    cout << "This program will determine if your brackets are matched." << endl;
    cout << "Please enter program code, followed by a period on a line by itself." << endl;

    oneLine = getLine();
    while (oneLine != ".") {
       allInput += oneLine + "\n";
       oneLine = getLine();
    }
    return allInput;
}

bool bracketsMatch(string input, char &unmatched) {
    Stack<char> s;

    for (char c : input) {
        // look for opening brackets
        if (openingBrackets.find(c) != string::npos) {
            s.push(c);
        }
        else {
            // look for closing brackets
            if (!closingBracketOkay(c,s)) {
                    unmatched = c;
                    return false;
            }
        }

    }
    // if we made it through the characters and the stack is not empty,
    // then we don't have a match :(
    if (!s.isEmpty()) {
        // report the top of the stack
        unmatched = s.pop();
        return false;
    }
    // We made it!
    return true;
}

bool closingBracketOkay(char c, Stack<char> &s) {
    char leftSymbol;

    // look for closing brackets
    if (closingBrackets.find(c) != string::npos) {
       if (s.isEmpty()) { // uh-oh!
           return false;
       }
       else {
           leftSymbol = s.pop();
           // check to see if the symbols are the same type
           if (openingBrackets.find(leftSymbol) != closingBrackets.find(c)) {
               // nope! :(
               return false;
           }
       }
    }
    return true;
}

void printInputWithLines(string input) {
    // count the number of lines
    int numLines = 1;
    for (char c : input) {
       if (c == '\n') {
           numLines++;
       }
    }
    // the log_10(numLines) is the maximum number of digits
    int maxDigits = log(numLines) / log(10);

    int lineNum = 0; // the first line
    int numDigits;
    for (char c : input) {
       if (lineNum == 0 || c == '\n') {
           if (lineNum != 0) {
               cout << endl;
           }
           lineNum++;
           numDigits = log(lineNum) / log(10);
           printSpaces(maxDigits - numDigits);
           cout << lineNum << "  ";
           if (lineNum == 1) {
               cout << c; // first character is special
           }
       }
       else {
           cout << c;
       }
    }
    cout << endl;
}

void printSpaces(int n) {
    for (int i=0; i < n; i++) {
        cout << " ";
    }
}
