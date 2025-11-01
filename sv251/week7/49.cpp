#include <iostream>
using namespace std;

int main() {
    int count;
    cout << "Enter a number: ";
    cin >> count;
    int i = 1;
    do {
        cout << i << endl;
        i++;
    } while (i <= count);

    return 0;
}