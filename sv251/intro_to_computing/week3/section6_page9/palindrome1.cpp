#include <iostream>
using namespace std;

bool palindrome1(string s);

int main() {
    string input;
    cout << "Enter anything (muhahaha): " << endl;
    cin >> input;
    if (palindrome1(input)) {
        cout << "This string is palindrome" << endl;
    }
    else {
        cout << "This string is not palindrome" << endl;
    }
    return 0;
}

bool palindrome1(string s) {
    string s1;
    for (int i = 0; i<s.length(); i++) {
        s1 += s[s.length()-1-i];
    }
    return (s == s1);
}