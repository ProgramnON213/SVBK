#include <iostream>
#include <cstring>
using namespace std;

// Student may implement another function as need

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {c -= ('a'-'A');}
    return c;
}
char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {c += ('a'-'A');}
    return c;
}
void process(const char *name, char *outstr) {
    int length = strlen(name);
    int idx = 0;
    bool inWord = false;
    
    for (int i = 0; i < length; i++) {
        if (isalpha(name[i])) {
            if (!inWord) {
                if (idx > 0) {outstr[idx++] = ' ';}
                outstr[idx++] = toUpper(name[i]);
                inWord = true;
            }
            else {
                outstr[idx++] = toLower(name[i]);
            }
        }
        else if (name[i] == ' ' || name[i] == '\t') {
                inWord = false;
            }
    }
    
    outstr[idx] = '\0';
    if (idx > 0 && outstr[idx-1] == ' ') {outstr[idx-1] = '\0';}
}

int main() {
    const int MAX_SIZE = 100;
char str[] = "Bui Gia B871978" ;
char outstr[MAX_SIZE];
process(str, outstr);
cout << outstr;
}