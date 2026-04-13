#include <iostream>
#include <iomanip>

using namespace std;

void findAllIndex(string s1, string s2) {
    // TO DO
    s2 = s2[0];
    #include <string>
    size_t pos = s1.find(s2);
    if (pos != string::npos) {
        cout << pos;
        pos = s1.find(s2, pos+1);
    }
    else {cout << -1; return;}
    while (pos != string::npos) {
        cout << " " << pos;
        pos = s1.find(s2, pos+1);
    }
}

int main () {
    string s1 = "bbb";
    string s2 = "ab";
    findAllIndex(s1, s2);
}