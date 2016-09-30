#include <iostream>
#include <string>
using namespace std;

#include "random.h"
#include "grid.h"
#include "simpio.h"
#include "filelib.h"

#include "gevents.h"
#include "gwindow.h"
#include "gobjects.h"

// the meat of the game
void doorOne(string & prize);
void doorTwo(string prize);
void doorThree(string & prize);

// main helper functions
void setUpGame();
void suspense();
int getChoice();

int main() {
    setUpGame();
    string prize = "some candy";

    int choice = getChoice();
    if(choice == 1) {
        doorOne(prize);
    } else if(choice == 2) {
        doorTwo(prize);
    } else if(choice == 3) {
        doorThree(prize);
    }

    suspense();
    cout << "You win " << prize << endl;
    return 0;
}

void doorOne(string & prize) {
    int dollars = 1 / 5 * 100;
    prize = "$" + integerToString(dollars);
}

void doorTwo(string prize) {
    prize = "a Maasai rungu";
}

void doorThree(string & prize) {
    prize = "a pineapple";
}

void setUpGame() {
    ifstream fileStream;
    openFile(fileStream, "welcome.txt");

    // get first line
    string numLinesStr;
    getline(fileStream, numLinesStr);
    int numLines = stringToInteger(numLinesStr);

    // output the welcome message
    for(int i = 0; i < numLines; i++) {
        string line;
        getline(fileStream, line);
        cout << line << endl;
    }
}

int getChoice() {
    string prompt = "Which door would you like to open (1, 2 or 3)?";
    while(true) {
        int choice = getInteger(prompt);
        if(choice < 1 || choice > 3) {
            cout << "Illegal door. Try again." << endl;
        } else {
            return choice;
        }
    }
}

void suspense() {
    cout << endl << "Dumroll!" << endl;
    for(int i = 0; i < 10; i++) {
        string line = "";
        for(int j = 0; j < (10 - i); j++) {
            line += ".";
        }
        cout << line << endl;
        pause(200);
    }
}
