#include<iostream>
#include<string>
using namespace std;
/* END of library */
bool palindrome(string strg);
bool palindromeRecursion(string s)
{
    // BEGIN YOUR IMPLEMENTATION [1]
    // TODO
    int size = (int) s.size();
    if (size == 1) {return true;}
    if (size == 2) {return s[0] == s[1];}
    string sub = s.substr(1, size-2);
    return (s[0] == s[size-1]) && palindromeRecursion(sub);
    // END YOUR IMPLEMENTATION [1]
}
int main()
{
    // BEGIN YOUR IMPLEMENTATION [2]
    // TODO
    string s;
    cin >> s;
    while (s[0] != '*') {
        cout << boolalpha << palindrome(s) << " " << palindromeRecursion(s) << endl;
        cin >> s;
    }
    // END YOUR IMPLEMENTATION [2]
    return 0;
}