#include <iostream>
#include <iomanip>
using namespace std;

float calculateBill(int k);

int main() {

    int k;
    char e;
    cout << "Input kWh consumed and E (Y/N): ";
    cin >> k >> e;
    if (e!='Y' && e!='N') {
        cout << "Invalid E input. Programn terminating." << endl;
        return 0;
    }
    float bill = calculateBill(k);
    if (e=='Y') {
        bill = bill * 1.05;
    }
    cout << setprecision(2) << fixed << bill << endl;
    return 0;
}

float calculateBill(int k) {
    float bill = 0;
    if (k > 300) {
        int kThisTier = k - 300;
        bill += kThisTier * 0.3;
        k -= kThisTier;
    }
    if (k > 200) {
        int kThisTier = k - 200;
        bill += kThisTier * 0.4;
        k -= kThisTier;
    }
    if (k > 100) {
        int kThisTier = k - 100;
        bill += kThisTier * 0.25;
        k -= kThisTier;
    }
    if (k > 50) {
        int kThisTier = k - 50;
        bill += kThisTier * 0.15;
        k -= kThisTier;
    }
    bill += k * 0.2;
    return bill;
}
