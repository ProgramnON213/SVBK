#include <iostream>
using namespace std;

int main() {
    int input, n = 7;
    do {
        cout << "Enter your guess: ";
        cin >> input;
        if (input != n) cout << "Wrong! Try again." << endl;
    } while (input != n);
    cout << "Correct! You win!" << endl;
}