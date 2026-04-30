#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <sstream>
int MAX_NUM_OF_BOOK = 100;
void manage(string library, string book, string author){
    // TODO
    string authorToSearch;
    string libraryToSearch;
    cin >> libraryToSearch;
    cin >> authorToSearch;
    bool found = false;

    // Search books written by author
    ifstream fAuthor(author);
    int books[MAX_NUM_OF_BOOK] = {0};
    int numOfAuthor;
    fAuthor >> numOfAuthor;
    string line;
    getline(fAuthor, line);
    while(getline(fAuthor, line)) {
        string currentAuthor;
        stringstream ss(line);
        ss >> currentAuthor;
        int bookID;
        if (currentAuthor == authorToSearch) {
            while (ss >> bookID) {
                books[bookID] = 1;
            }
            break;
        }
    }
    fAuthor.close();

    // Search library and see their books
    ifstream fLibrary(library);
    int numOfLibs;
    fLibrary >> numOfLibs;
    getline(fLibrary, line);
    while (getline(fLibrary, line)) {
        stringstream ss(line);
        string currentLib;
        ss >> currentLib;
        int bookID;
        if (currentLib == libraryToSearch) {
            while (ss >> bookID) {
                if (books[bookID] == 1) {
                    found = true;
                    break;
                }
            }
            break;
        }
    }

    if (found) {cout << "True";}
    else {cout << "False";}
}

int main() {
    manage("file3Library.txt", "file3Book.txt", "file3Author.txt");
}