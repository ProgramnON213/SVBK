#include <iostream>
using namespace std;

bool isHawaiian(string s);
bool isVowel(char c);
bool isConsonant(char c);
bool isWhitespace(char c);
string consonantBeforeAndCurrent(char before, char current);
string consonantSingle(char c);
string vowelCurrentAndAfter(char current, char after);
string vowelSingle(char s);

int main() {
    string input, s, ans = "";
    getline(cin, input);
    int length = input.size();

    for (char c : input)    {
        string temp(1, tolower(c));
        s.append(temp);
    }

    if (!isHawaiian(s)) {
        cout << input << " contains invalid characters." << endl; // Add warning here
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (isConsonant(s[i])) {
            if (i-1 < 0 || isWhitespace(s[i-1]))    ans.append(consonantSingle(s[i]));  // Start of a word
            else ans.append(consonantBeforeAndCurrent(s[i-1], s[i]));
        }
        else if (isVowel(s[i])) {
            if (i == length - 1)    ans.append(vowelSingle(s[i]));
            else if (vowelCurrentAndAfter(s[i], s[i+1]) == "xx") {
                ans.append(vowelSingle(s[i]));
            }
            else {
                ans.append(vowelCurrentAndAfter(s[i], s[i+1]));
                i++;
            }
            if (!(isWhitespace(s[i+1]) || i == length - 1))   ans.append("-");
        }
        else if (isWhitespace(s[i])) {
            string temp(1, s[i]);
            ans.append(temp);
        }
    }

    cout << ans << endl;

    return 0;
}

bool isHawaiian(string s) {
    char alphabet[14] = {'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', '\'', ' '};
    for (char c : s) {
        bool found = false;
        c = tolower(c);
        for (int i = 0; i < 14; i++) {
            if (c == alphabet[i])  found = true;
        }
        if (!found) return false;
    }
    return true;
}

bool isVowel(char c) {
    char vowels[5] = {'a', 'i', 'u', 'e', 'o'};
    for (int i = 0; i < 5; i++) {
        if (c == vowels[i]) return true;
    }
    return false;
}

bool isConsonant(char c) {
    char consonants[7] = {'p', 'k', 'h', 'l', 'm', 'n', 'w'};
    for (int i = 0; i < 7; i++) {
        if (c == consonants[i]) return true;
    }
    return false;
}

bool isWhitespace(char c) {
    char whitespaces[2] = {' ', '\''};
    for (int i = 0; i < 2; i++) {
        if (c == whitespaces[i]) return true;
    }
    return false;
}

string consonantSingle(char c) {
    string s(1, c);
    return s;
}

string consonantBeforeAndCurrent(char before, char current) {
    if (current != 'w') {
        string s(1, current);
        return s;
    } else if (before == 'i' || before == 'e') return "v";
    return "w";
}

string vowelCurrentAndAfter(char current, char after) {
    string temp = {current, after};
    if (temp == "ai")   return "eye";
    if (temp == "ae")   return "eye";
    if (temp == "ao")   return "ow";
    if (temp == "au")   return "ow";
    if (temp == "ei")   return "ay";
    if (temp == "eu")   return "eh-oo";
    if (temp == "iu")   return "ew";
    if (temp == "oi")   return "oy";
    if (temp == "ou")   return "ow";
    if (temp == "ui")   return "ooey";
    return "xx";
}

string vowelSingle(char s) {
    if (s == 'a')   return "ah";
    if (s == 'e')   return "eh";
    if (s == 'i')   return "ee";
    if (s == 'o')   return "oh";
    if (s == 'u')   return "oo";
    return "xx";
}