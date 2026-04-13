#include <iostream>
#include <iomanip>

using namespace std;

void cutString(string s, int index){
    // TO DO
    #include <string>
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    if (index >= length) {return;}
    cout << s.substr(index);
}

int main () {
    string s = "Truong Dai Hoc Bach Khoa.";
    cutString(s, 7);
    string s1 = "BK";
    cutString(s1, 0);
    string s2 = "BKFC";
    cutString(s2, 4);
}