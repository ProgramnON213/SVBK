#include <iostream>
using namespace std;

#include <cstring>
char caesarChar(char i, int key) {
    key %= 26;
    int c = (int) i;
    if (47 < c && c < 58) {
         c += key;
         if (c < 48)    c += 10;
         else if (c > 57)   c -= 10;
    }
    else if (64 < c && c < 91) {
        c += key;
        if (c < 65)     c += 26;
        else if (c > 90)    c -= 26;
    }
    else if (96 < c && c < 123) {
        c += key;
        if (c < 97)     c += 26;
        else if (c > 122)   c -= 26;
    }
    return (char) c;
}

void encrypt(char* text, int shift) {
    // Write your code 
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        text[i] = caesarChar(text[i], shift);
    }
}

void decrypt(char* text, int shift) {
    // Write your code 
    encrypt(text, -shift);
}

int main() {
    int n, shift; 
    cin >> n >> shift;
    char* text = new char[n+1];
    for(int i = 0; i < n; i++) cin >> text[i];
    text[n] = 0;

    encrypt(text, shift);
    cout << text << '\n';
    decrypt(text, shift);
    cout << text;

    delete[] text;
}