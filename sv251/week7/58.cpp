#include <iostream>
using namespace std;

int main() {
    cout << "Input 2 numbers, then a matrix. ";
    int r, c;
    cin >> r >> c;
    int sum = 0;
    int input;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> input;
            if (i==0||j==0||i==r-1||j==c-1) sum += input;
        }
    }

    cout << sum << endl;

    return 0;
}