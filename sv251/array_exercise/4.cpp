// (Homework - send your work to Ms. Minh Hua by email within 12th Nov for bonus) Input an 2-dimensional array M x N. Print the elements arr[i][j] that have (i+j) divided by 5

#include <iostream>
using namespace std;

int main() {
    int M, N;
    cout << "Enter size of a two dimensional array: ";
    cin >> M >> N;
    int arr[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {

            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if ((i+j) % 5 == 0) cout << arr[i][j] << " ";
        }
    }
    cout << endl;
}