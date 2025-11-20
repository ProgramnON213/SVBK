#include <iostream>
using namespace std;

int main() {
    char ch;
    cin >> ch;
    
    if ((ch>=65 && ch<=90) || (ch>=97 && ch<=122)) {
        if (ch < 95) ch += 7+25;
        if (ch == 65 || ch == 69 || ch == 73 || ch == 79 || ch == 85 || ch == 97 || ch == 101 || ch == 105 || ch == 111 || ch == 117) { 
            if (ch < 95) ch += 7+25;
            cout << ch << " is a vowel.";
        }
        else cout << ch << " is a consonant.";
    } else cout << "The character is not a letter.";
    
    return 0;
}
