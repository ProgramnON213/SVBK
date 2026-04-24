#include <iostream>
#include "Book.h"

using namespace std;

// Initialize the static variable
int Book::count = 0; 

// Use the Book:: prefix to implement the methods declared in the header
Book::Book() {
    title = "temp";
    author = "Unknown";
    price = 0.0;
    quantity = 0;
    count++; // Track the simulation
}

Book::Book(string t, string a, double p, int q) {
    title = t;       // Fixed shadowing
    author = a;
    setPrice(p);
    setQuantity(q);
    count++;
}

Book::Book(string t, string a) {
    title = t;
    author = a;
    setPrice(0);
    setQuantity(0);
    count++;
}

Book::~Book() {
    cout << "Deleting books with title: " << title << endl;
    count--; // Decrement when destroyed
}

void Book::setPrice(double p) {
    if (p >= 0) {
        price = p;
    }
}

void Book::setQuantity(int q) {
    if (q >= 0) {
        quantity = q;
    }
}

string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
double Book::getPrice() const { return price; }
int Book::getQuantity() const { return quantity; }
double Book::getTotalValue() const { return quantity * price; }

void Book::sell(int n) {
    if (n > quantity) { cout << "Not enough quantity" << endl; }
    else {
        quantity -= n;
        cout << "Sold " << n << " copies of " << title << "." << endl;
        cout << "Remaining: " << quantity << endl;
    }
}

void Book::restock(int n) {
    if (n < 0) {return;}
    quantity += n;
    cout << "Restocking " << title << "." << endl;
    cout << "Quantity: " << quantity << endl;
}

void Book::display() const {
    cout << "\n";
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: " << price << endl;
    cout << "\n";
}