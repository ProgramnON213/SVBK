#include <iostream>
using namespace std;

int const SENTINEL = -1;

int main() {
    int input = 50;
    int sum = 0;
    do {
        cout << "Input a number: ";
        cin >> input;
        if (input > 0 && input < 100) {
            sum += input;
        }
    } while (input != SENTINEL);
    cout << sum << endl;
}