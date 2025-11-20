#include <iostream>
using namespace std;

int main () {
    int score;
    cout << "Input score: ";
    cin >> score;
    if (score < 0 || score > 100) {
        cout << "Invalid input. Score must be between 0 and 100" << endl;
    } else {
        if (score >= 90) {
            cout << "Scholarship awarded" << endl;
        } else {
            cout << "Scholarship not awarded" << endl;
        }
    }
    return 0;
}