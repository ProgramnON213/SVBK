#include <iostream>
using namespace std;

#include <cstring>
bool isPalindrome(const char* str) {
    // Write your code here
    int length = strlen(str);
    int i = 0;
    while (i < length - i - 1) {
        if (str[i] != str[length-i-1]) {return false;}
        i++;
    }
    return true;
}

int main() {
    const char* str1 = "abba";
    cout << isPalindrome(str1);

    const char* str2 = "axz";
    cout << isPalindrome(str2);
}