// Simple Stack Example

#include <iostream>
#include "console.h"
#include "stack.h"

using namespace std;
const char SPACE = ' ';

int main() {
    string sentence = "hope is what defines humanity";
    string word;
    Stack<string> wordStack;

    cout << "Original sentence: " << sentence << endl;

    for (char c : sentence) {
       if (c == SPACE and word != "") {
           wordStack.push(word);
           word = ""; // reset
       }
       else {
           word += c;
       }
    }
    if (word != "") {
        wordStack.push(word);
    }

    cout << "     New sentence: ";
    while (!wordStack.isEmpty()) {
        string word = wordStack.pop();
        cout << word << SPACE;
    }
    cout << endl;

    return 0;
}
