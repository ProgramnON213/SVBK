#include <iostream>
using namespace std;

class Integer 
{
    public:
    Integer();
    Integer(int n);
    void setValue(int n);
    int getValue() const;
    
    private:
    int val;
};

void Integer::setValue(int n) {
    this->val = n;
    return;
}

int Integer::getValue() const {
    return val;
}

Integer::Integer() {
    this->val = 0;
}

Integer::Integer(int n) {
    this->val = n;
}

int main() {
    cout<<"Constructor test";
    Integer i(10);
    Integer i2(-10);
    Integer *i3=new Integer(20);
    delete i3;
}