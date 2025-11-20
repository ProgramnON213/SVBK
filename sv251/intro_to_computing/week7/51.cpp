#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int x, y;
    cout << "Input 2 numbers: ";
    cin >> x >> y;
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            cout << setw(5) << i * j;
        }
        cout << endl;
    }

    return 0;
}