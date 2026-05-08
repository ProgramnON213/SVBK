#include <iostream>
using namespace std;

char* concatStr(char* str1, char* str2) {
    // TODO
    int n1 = 0; int n2 = 0;
    while (str1[n1] != '\0') {n1++;}
    while (str2[n2] != '\0') {n2++;}
    char* s = new char[n1 + n2 + 1];

    for (int i = 0; i < n1; i++) {
        s[i] = str1[i];
    }

    for (int i = 0; i < n2; i++) {
        s[i + n1] = str2[i];
    }

    s[n1+n2] = '\0';
    return s;
}

int main() {
    char s1[] = "Hello, ";
    char s2[] = "how are you?";
    char* s = concatStr(s1, s2);
    cout << s;
    delete[] s;
}