#include <iostream>
using namespace std;

int main() {

    int count = 1;
    double num;

    while (count <= 10 && num <= 76)
{
    cout << "Enter a number: ";    cin >> num;
    if (num > 76) {
         cout << "you lose!\n";
    }
    else
       cout << "Keep on trucking!\n";
    count++;
}

}