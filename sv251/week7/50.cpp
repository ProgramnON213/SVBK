#include <iostream>
using namespace std;

int main() {
    int count;
    cout << "Enter a number: ";
    cin >> count;
    int i = 2;
    int sum = 0;
    do {
        sum += i;
        i+=2;
    } while (i <= count);
    cout << sum << endl;

    return 0;
}