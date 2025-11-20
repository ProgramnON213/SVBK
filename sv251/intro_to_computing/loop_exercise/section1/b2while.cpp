#include <iostream>
using namespace std;

int main() {
    double N, sum = 0;
    cout << "Input number N: ";
    cin >> N;
    double input = N + 1;
    while (input != N) {
        cout << "Input a number: ";
        cin >> input;
        sum += input;
    }
    cout << sum - N << endl;
}