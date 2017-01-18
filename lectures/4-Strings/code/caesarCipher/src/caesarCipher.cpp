// Caesar Cipher example

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"

using namespace std;

// function prototype
string cipher(string plaintext, int key);

int main() {
    string plainText = getLine("Please enter some plain text: ");
    int key = -1; // start with an invalid key for the while loop
    while (key < 1 || key > 25) {
            key = getInteger("Please enter an integer between 1 and 25");
    }
    string cipherText = cipher(plainText, key);

    cout << "Plain text:  " << plainText << endl;
    cout << "Cipher text: " << cipherText << endl;
    return 0;
}

string cipher(string plainText, int key){
    // only works for uppercase!
    plainText = toUpperCase(plainText);
    string cipherText;
    for (int i=0;i<(int)plainText.length();i++) {
        char plainChar = plainText[i];
        char cipherChar;
        if (plainChar >= 'A' && plainChar <= 'Z') {
            cipherChar = plainText[i] + key;
            if (cipherChar > 'Z') {
                cipherChar -= 26; // wrap back around
            }
        } else {
            cipherChar = plainChar;
        }
        cipherText += cipherChar;
    }
    return cipherText;
}
