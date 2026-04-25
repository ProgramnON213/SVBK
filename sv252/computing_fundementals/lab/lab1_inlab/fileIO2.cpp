#include <iostream>
#include <fstream>
using namespace std;

void process(string fileName)   {
    // TODO
    ifstream f(fileName);
    int row, col;
    f >> row >> col;
    float totalMax, rowMax;
    streampos temp = f.tellg();
    f >> totalMax;
    f.seekg(temp);
    for (int i = 0; i < row; i++) {
        streampos temp = f.tellg();
        f >> rowMax;
        f.seekg(temp);
        for (int j = 0; j < col; j++) {
            float n;
            f >> n;
            if (n > rowMax) {
                rowMax = n;
            }
        }
        cout << rowMax << " ";
        if (rowMax > totalMax) {
            totalMax = rowMax;
        }
    }
    cout << totalMax;
}

int main() {
    process("fileIO2Test1.txt");
}