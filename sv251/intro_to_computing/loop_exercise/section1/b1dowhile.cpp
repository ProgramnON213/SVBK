#include <iostream>
using namespace std;

int main() {
    double N;
    cout << "Input number N: ";
    cin >> N;
    double input;
    do {
        cout << "Input number: ";
        cin >> input;
    } while (input != N);
}