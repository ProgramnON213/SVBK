#include <iostream>
#include <math.h>
using namespace std;

float calculateDistance(int pos_x, int pos_y, int cen_x, int cen_y) {
    float distance = sqrt((pos_x - cen_x)^2 + (pos_y - cen_y)^2);
    return distance;
}

int main() {
    cout << "Enter number: ";
    int n;
    cin >> n;
    int cen_x = n/2 - 1;
    int cen_y = n/2 - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (calculateDistance(i, j,cen_x, cen_y) < 0.5) {
                cout << "*";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}