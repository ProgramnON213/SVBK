#include <iostream>
using namespace std;

int main() {
    int N, sum = 0;
    cout << "Input number N: ";
    cin >> N;
    int input = N + 1;
    while (input != N) {
        cout << "Input a number: ";
        cin >> input;
        if (input % 2 == 0) sum += input;
    }
    cout << sum << endl;
}