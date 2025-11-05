#include <iostream>
using namespace std;

int main() {
    double N;
    cout << "Input number N: ";
    cin >> N;
    double input = N + 1;
    while (input != N) {
        cout << "Input a number: ";
        cin >> input;
    }
}