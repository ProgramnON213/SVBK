#include <iostream>
using namespace std;

int main() {
    int count = 0;
    double grade, total = 0;
while (count < 30) {
    cout << "Enter a grade: ";
    cin >> grade;
    if (!(grade < 0 || grade > 100)) {
        total = total + grade;
        count++;
    }
}

}