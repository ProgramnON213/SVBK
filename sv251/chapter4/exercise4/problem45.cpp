#include <iostream>
using namespace std;

int main () {
    double work;
    int start;
    cout << "Input workhour and startday: ";
    cin >> work >> start;
    if (work <= 66) {
        cout << "No extra hour needed" << endl;
    } else if (work <= 78) {
        cout << "Need extra hour" << endl;
    } else if (work <= 82 && start==1) {
        cout << "Need all the extra hour" << endl;
    }   else {
        cout << "Not doable" << endl;
    }
    return 0;
}