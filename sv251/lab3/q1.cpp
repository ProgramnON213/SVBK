#include <iostream>
using namespace std;

int main() {
    int max, min, temp;
    cin >> max >> min;
    if (max < min) {
        temp = min;
        min = max;
        max = temp;
    }
    if (!(min == 0))
    while (max % min != 0) {
        temp = max % min;
        max = min;
        min = temp;
    }
    else min = max;
    cout << min;
}