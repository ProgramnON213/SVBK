#include <iostream>
#include <fstream>
using namespace std;

void display(int table[4]) {
    cout << "A " << table[0] << endl;
    cout << "B " << table[1] << endl;
    cout << "C " << table[2] << endl;
    cout << "D " << table[3] << endl;
}

void studentGrading(string fileName) {
    // TODO
    ifstream f(fileName);
    int numOfStudent;
    f >> numOfStudent;
    float avg, temp;
    bool fail = false;
    int table[4] = {0};
    for (int i = 0; i < numOfStudent; i++) {
        avg = 0;

        for (int j = 0; j < 4; j++) {
            f >> temp;
            if (temp < 5) {fail = true;}
            avg += temp;
        }

        if (!fail) {
            avg /= 4.0;
            if (avg >= 8) {table[0]++;}
            else if (avg >= 6.5) {table[1]++;}
            else if (avg >= 5) {table[2]++;}
            else {table[3]++;}
        }
        else {
            table[3]++;
            fail = false;
        }
    }
    display(table);
}

int main() {
    studentGrading("file1a.txt");
}