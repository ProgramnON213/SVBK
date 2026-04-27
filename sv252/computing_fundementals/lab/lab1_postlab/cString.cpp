#include <iostream>
#include <cstring>
using namespace std;

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {return c - ('a' - 'A');}
    return c;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {return c + ('a' - 'A');}
    return c;
}

void process(const char *name, char *outstr) {
    // TODO
    int nameLength = strlen(name);
    bool isNewWord = true;
    int index = 0;
    for (int i = 0; i < nameLength; i++) {
        if (isalpha(name[i])) {
            if (isNewWord) {
                outstr[index] = toUpper(name[i]);
                index++;
                isNewWord = false;
            }
            else {
                outstr[index] = toLower(name[i]);
                index++;
            }
            if (i < nameLength-1 && !(isalpha(name[i+1]))) {
                isNewWord = true;
                outstr[index] = ' ';
                index++;
            }
        }
    }
    if(outstr[index-1] == ' ') {outstr[index-1] = '\0';}
}

int main() {
    const int MAX_SIZE = 100;
char str[] = "Bui Gia B871978" ;
char outstr[MAX_SIZE];
process(str, outstr);
cout << outstr;
}