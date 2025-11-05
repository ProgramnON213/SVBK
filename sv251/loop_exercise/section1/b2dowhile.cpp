#include <iostream>
using namespace std;

int main() {
    double N, sum = 0;
    cout << "Input number N: ";
    cin >> N;
    double input ;
    do {
        cout << "Input a number: ";
        cin >> input;
        sum += input;
    } while (input != N);
    cout << sum - N << endl;
}