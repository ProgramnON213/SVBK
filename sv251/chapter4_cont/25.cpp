#include <iostream>
using namespace std;

int main() {
    cout << "Enter two numbers: ";
    int max, min, temp;
    cin >> max >> min;
    if (max < min) {
        temp = min;
        min = max;
        max = temp;
    }
    while (max % min != 0) {
        temp = max % min;
        max = min;
        min = temp;
    }
    cout << min << endl;
}