#include <iostream>
using namespace std;

int main() {
    int days, years, weeks, remaining_days;
    
    cin >> days;
    years = days / 365;
    days = days % 365;
    weeks = days / 7;
    remaining_days = days % 7;

    cout << years << " years + "
         << weeks << " weeks + "
         << remaining_days << " days";

    return 0;
}
