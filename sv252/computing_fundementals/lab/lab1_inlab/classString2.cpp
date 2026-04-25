#include <iostream>
#include <string>
using namespace std;

void deleteWord(string s, string s1){
    //TO DO
    size_t pos = s.find(s1);
    while (pos != string::npos) {
        s.replace(pos, s1.length(), "");
        pos = s.find(s1);
    }
    cout << s;
}

int main() {
    string s = "Truong Dai Hoc Bach Khoa, Sai Gon";
    string s1 = "ai ";
    deleteWord(s, s1);
}