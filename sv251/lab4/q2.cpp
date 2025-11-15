#include <iostream>
#include <string>
using namespace std;

int minOperations(string s);

int main() {
    cout << minOperations("0100");
    return 0;
}

int minOperations(string s) {
    int length = s.length();
    char s1[length];
    int count1 = 0, count2 = 0;
    for (int i = 0; i < length; i++) {
        if (i%2)    s1[i] = '0';
        else s1[i] = '1';
    }
    for (int i = 0; i < length; i++) {
        if (s[i] != s1[i]) count2++;
        else    count1++;
    }
    return min(count1, count2);
}