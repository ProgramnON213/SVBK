#include <iostream>
#include <string>
using namespace std;

int minOperations(string s);

int main() {
    cout << minOperations("0100");
    return 0;
}

int minOperations(string s) {
    int count_0 = 0, count_1 = 0;
    for (size_t i = 0; i < s.length() ; i++) {
        if (s[i] == '0')    count_0++;
        else    count_1++;
    }
    int differences = count_0 - count_1;
    if (differences < 0) differences = -differences;

    return differences / 2;
}