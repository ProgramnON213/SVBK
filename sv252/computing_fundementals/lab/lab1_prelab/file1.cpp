#include <iostream>
#include <fstream>
using namespace std;

void calSum(string fileName)   {
    // TODO
    int num; int sum = 0;
    ifstream f(fileName);
    while (!f.eof()) {
        f >> num;
        if (num > 0) {sum += num;}
    }
    f.close();
    cout << sum;
}

int main() {
    calSum("file1a.txt");
}