#include <iostream>
using namespace std;

int main() {
    int n, ans = 77;
    do {
        cout << "Enter guess: ";
        cin >> n;
        if (n < ans) cout << "Too low!" << endl;
        else if (n > ans) cout << "Too high!" << endl;
    } while (n != ans);
    cout << "Correct!" << endl;
}