#include <iostream>
using namespace std;

bool isSymmetry(int *head, int *tail) {
    int *temp = tail;
    while (head != tail && head != temp) {
        if (*head != *tail) {return false;}
        temp = tail;
        head++;
        tail--;
    }
    return true;
}

int main() {
    int arr[] = {4, 2, 2, 4};
    cout << isSymmetry(arr, arr + (sizeof(arr) / sizeof(arr[0])) - 1);
}