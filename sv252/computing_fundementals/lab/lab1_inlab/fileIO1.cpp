#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string upper(string text) {
    for (int i = 0; i < text.size(); i++) {
        if (text[i] >= 97 && text[i] <= 122) {
            text[i] -= 32;
        }
    }
    return text;
}

void uppercase(string output)   {
    // TODO
    ofstream f(output);
    string input;
    cin >> input;
    input = upper(input);
    f << input;
}

int main() {
    uppercase("fileIO1Test1.txt");
}