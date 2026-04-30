#include <iostream>
using namespace std;

#include <cstring>
void mostFrequentCharacter(char* str, char& res, int& freq) {
    // Write your code 
    int length = strlen(str);
    int table[26] = {0};
    for (int i = 0; i < length; i++) {
        table[tolower(str[i]) - 'a']++;
    }
    freq = table[0];
    res = 'a';
    for (int i = 0; i < 26; i++) {
        if (table[i] > freq) {
            freq = table[i];
            res = i + 'a';
        }
    }
}

int main() {
    int n;
    cin >> n;
    char* str = new char[n+1];
    for(int i = 0; i < n; i++) cin >> str[i];
    str[n] = 0;
    char res = 0;
    int freq = 0;
    mostFrequentCharacter(str, res, freq);
    cout << res << ' ' << freq;
    delete[] str;
}