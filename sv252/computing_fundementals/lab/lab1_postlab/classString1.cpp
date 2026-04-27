#include <iostream>
#include <string>

using namespace std;

int countLengthPalindromeWithIndexAtCenter(string s, int index) {
    int i = 0;
    while (index - i >= 0 && index + i < s.size()) {
        if (s[index-i] != s[index+i]) {break;}
        i++;
    }
    i--;
    return 2*i + 1;
}

int countLengthPalindromeWithCenterRightOfIndex(string s, int index) {
    int i = 0;
    while (index - i >= 0 && index + i + 1 < s.size()) {
        if (s[index-i] != s[index+i+1]) {break;}
        i++;
    }
    return 2*i;
}

string longestPalindrome(string s) {
    string ans = "";
    int maxLength = 0;
    int maxAtIndex = 0;
    bool isPalindromeOdd = false;
    int palLength;
    for (int i = 0; i < s.size(); i++) {
        palLength = countLengthPalindromeWithIndexAtCenter(s, i);
        if (palLength > maxLength) {
            maxLength = palLength;
            maxAtIndex = i;
            isPalindromeOdd = true;
        }
        palLength = countLengthPalindromeWithCenterRightOfIndex(s, i);
        if (palLength > maxLength) {
            maxLength = palLength;
            maxAtIndex = i;
            isPalindromeOdd = false;
        }
    }

    int start, end;
    if (isPalindromeOdd) {
        start = maxAtIndex - (maxLength-1)/2;
        end = maxAtIndex + (maxLength-1)/2;
    }
    else {
        start = maxAtIndex - (maxLength)/2 + 1;
        end = maxAtIndex + maxLength/2;
    }

    for (int i = start; i <= end; i++) {
        ans += s[i];
    }
    return ans;
}

int main()  {
    // TODO
    string s;
    cin >> s;
    cout << longestPalindrome(s);
}