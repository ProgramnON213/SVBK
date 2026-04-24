#pragma once
#include <string>
using namespace std;

class Book {
    private:
    string title;
    string author;
    double price;
    int quantity;

    public:
    static int count;

    Book ();
    Book (string title, string author, double price, int quantity);
    Book (string title, string author);
    ~Book();

    void setPrice(double p);
    void setQuantity(int q);
    string getTitle() const;
    string getAuthor() const;
    double getPrice() const;
    int getQuantity() const;
    double getTotalValue() const;
    void sell(int n);
    void restock(int n);
    void display() const;
    
    static int getCount();
};