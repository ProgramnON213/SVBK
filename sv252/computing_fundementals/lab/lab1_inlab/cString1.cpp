#include <iostream>
#include <cstring>
using namespace std;

int find(char str[], char substr[]) {
    // TODO
    int lengthStr = strlen(str);
    int lengthSubStr = strlen(substr);
    char firstChar = substr[0];
    for (int i = 0; i < lengthStr; i++) {
        if (str[i] == firstChar) {
            for (int j = 0; j < lengthSubStr; j++) {
                if (str[i+j] != substr[j]) {break;}
                if (j == lengthSubStr-1) {return i;}
            }
        }
    }
    return -1;
}

int main() {

}