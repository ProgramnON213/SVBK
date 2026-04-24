#include <iostream>
#include "Book.h"

using namespace std;

int main() {
    Book book1;
    Book book2("Harry Potter and the Deathly of Hallows", "J.K.Rowling");
    Book book3("Huong dan thi nghiem", "Tran Tuan Anh", 15, 100);

    book1.display();
    book2.display();
    book3.display();

    book3.sell(7);
    book3.restock(14);
    book3.display();

    cout << Book::count << endl;

    Book books[] = {book1, book2};

    Book *p_book1 = &book1;
    p_book1->display();
}