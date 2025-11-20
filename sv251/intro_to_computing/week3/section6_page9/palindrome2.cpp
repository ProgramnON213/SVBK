#include <iostream>
using namespace std;

bool palindrome2(string s);

int main() {
    string input;
    cout << "Enter anything (muhahaha): " << endl;
    cin >> input;
    if (palindrome2(input)) {
        cout << "This string is palindrome" << endl;
    }
    else {
        cout << "This string is not palindrome" << endl;
    }
    return 0;
}

bool palindrome2(string s) {
    if (s.length() < 2) {
        return true;
    }
    if (s[0] != s[s.length()-1]) {
        return false;
    }
    else {
        string temp;
        for (int i = 1; i < s.length()-1; i++) {
            temp += s[i];
        }
        return palindrome2(temp);
    }
}