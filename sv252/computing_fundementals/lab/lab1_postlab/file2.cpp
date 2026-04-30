#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <sstream>
class Product {
    public:
    int id;
    int price;
};

void calMoney(string price, string buy) {
    // TODO
    ifstream f(price);
    int numOfProducts;
    f >> numOfProducts;
    Product products[20];
    for (int i = 0; i < numOfProducts; i++) {
        f >> products[i].id;
        f >> products[i].price;
    }
    f.close();
    f.clear();

    f.open(buy);
    int numOfBuyers;
    f >> numOfBuyers;
    string line;
    getline(f, line);
    while (getline(f, line)) {
        stringstream ss(line);
        string id;
        int productID, quantity;
        int total = 0;
        ss >> id;
        while (ss >> productID >> quantity) {
            for (int i = 0; i < numOfProducts; i++) {
                if (products[i].id == productID) {
                    total += quantity*products[i].price;
                    break;
                }
            }
        }
        cout << id << " " << total << endl;
    }
}

int main() {
    calMoney("file2a1.txt", "file2a2.txt");
}