#include <iostream>
using namespace std;

int** readArray() {
    int** res = new int*[10];
    for (int i = 0; i < 10; i++) {
        res[i] = new int[10];
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int n;
            cin >> n;
            if (n == 0) {
                for (int k = j; k < 10; k++) {
                    res[i][k] = 0;
                }
                break;
            }
            res[i][j] = n;
        }
    }
    return res;
}

int main() {
    readArray();
}