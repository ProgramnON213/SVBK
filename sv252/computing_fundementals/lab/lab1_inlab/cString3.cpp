#include <iostream>
#include <cstring>
using namespace std;

void process(char str[], char outstr[]) {
    // TODO
    outstr[0] = '\0';
    char *pos = strtok(str, " ");
    while (pos != NULL) {
        strcat(outstr, pos);
        strcat(outstr, " ");
        pos = strtok(NULL, " ");
    }
    outstr[strlen(outstr)-1] = '\0';
}

int main() {
    const int MAX_SIZE = 100;
    char str[] = "  abc  def  ghi  " ;
    char outstr[MAX_SIZE];
    process(str, outstr);
    cout << outstr;
}