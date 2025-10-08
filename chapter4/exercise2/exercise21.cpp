#include <iostream>
using namespace std;

int main () {
    int score;
    cout << "Input score: ";
    cin >> score;
    if (score >= 90) {
        cout << "Scholarship awarded" << endl;
    } else {
        cout << "Scholarship not awarded" << endl;
    }
    return 0;
}