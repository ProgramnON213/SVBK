#include <iostream>
#include <iomanip>

using namespace std;

void recover(char signal[]) {
    // TODO
    int i = 0;
    while (signal[i] != '\0') {
        if (signal[i] > 64 && signal[i] < 91) {
            signal[i] += 32;
        }
        else if (signal[i] > 96 && signal[i] < 123) {
            signal[i] -= 32;
        }
        i++;
    }
}

int main () {
    char signal[] = "hello world" ;
    recover(signal);
    cout << signal << endl;

    char signal0[] = "CSE HCMUT" ;
    recover(signal0);
    cout << signal0 << endl;

    char signal1[] = "I waNT tO hAVe 10 MaRk In FudaMenTAL of PRogRamInG couRsE." ;
    recover(signal1);
    cout << signal1 << endl;

    char signal2[] = "aAzZ";
    recover(signal2);
    cout << signal2 << endl;
}