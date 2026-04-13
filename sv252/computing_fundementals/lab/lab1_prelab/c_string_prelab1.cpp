#include <iostream>
#include <iomanip>

using namespace std;

void reverse(char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    int start = 0; int end = length-1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int main () {
    const int MAX_SIZE = 100;
    char str[] = "";
    reverse(str);
    cout << str;
}