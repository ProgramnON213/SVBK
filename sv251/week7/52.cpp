#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int w, h;
    cout << "Input 2 numbers: ";
    cin >> w >> h;
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}