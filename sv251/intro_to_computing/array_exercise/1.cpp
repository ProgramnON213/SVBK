#include <iostream>
using namespace std;

int main() {
    cout << "Input array size: ";
    int N;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++) {
        cout << "Input a number: ";
        cin >> arr[i];
    }
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}