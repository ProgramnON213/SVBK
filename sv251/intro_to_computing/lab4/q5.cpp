#include <iostream>
#include <string>
using namespace std;

bool palindrome(string s);

int main() {
    cout << palindrome("race a car");
    return 0;
}

bool palindrome(string s) {
    int length = s.length(), real_length = 0;
    string s1[length];
    for (int i = 0; i < length; i++) {
        if (s[i] >= 65 && s[i] <= 90)   s[i] +=32;
        if ((s[i] >= 97 && s[i] <= 122) || (s[i] >= 48 && s[i] <= 57)) {
            s1[real_length] = s[i];
            real_length += 1;
        }
    }
    string s2[real_length];
    for (int i = 0; i < real_length; i++) {
        s2[i] = s1[real_length - i - 1];
    }

    bool result = true;
    for (int i = 0; i < real_length; i++) {
        if (s1[i] != s2[i]) {
            result = false;
            break;
        }
    }
    return result;
}