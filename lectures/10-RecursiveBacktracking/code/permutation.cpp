#include <iostream>
#include "console.h"

using namespace std;

// permute a string of length 4
void permute4(string s) {
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

void recPermuteHelper(string soFar, string rest)
{
    if (rest.empty()) {
        cout << "  " << soFar << endl;
    } else {
        for (int i = 0; i < (int)rest.size(); i++) {
            string remaining = rest.substr(0, i)
                    + rest.substr(i+1);
            recPermuteHelper(soFar + rest[i], remaining);
        }
    }
}

void recPermute(string s) {
    recPermuteHelper("",s);
}

int main() {
    permute4("abcd");
    cout << endl << endl;
    recPermute("abcdef");
    return 0;
}
