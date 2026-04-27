#include <iostream>
#include <string>
using namespace std;

bool isUnique(string s) {
    char seenTable[128] = {0};
    for (int i = 0; i < s.size(); i++) {
        if (seenTable[s[i]] > 0) {return false;}
        seenTable[s[i]]++;
    }
    return true;
}

int longestNonRepeatSubString(string s) {
    // TO DO 
    if (s.size() == 0) {return 0;}
    char seenTable[128] = {0};
    int maxLength = 1;
    int l = 0;
    for (int r = 0; r < s.size(); r++) {
        while (s[r] == 1) {
            s[l] = 0;
            l++;
        }
        maxLength = max(maxLength, r-l+1);
    }
    return maxLength;
}

int main()  {
    string s;
    cin >> s;
    cout << longestNonRepeatSubString(s);
    return 0;
}