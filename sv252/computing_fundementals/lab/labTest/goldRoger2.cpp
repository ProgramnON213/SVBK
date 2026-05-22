#include <iostream>
using namespace std;

class Pirate {
    public:
    string name;
    int bounty;
    Pirate* next;

    Pirate(string name, int bounty);
    friend ostream& operator<<(ostream& os, const Pirate& pirate);
};

class Crew {
    public:
    string name;
    Pirate* crewmate;

    Crew(string name, Pirate* captain);
    void add(string name, int bounty);
    void printCrew();
};

ostream& operator<<(ostream& os, const Pirate& pirate) {
    os << "Pirate: [Name: " << pirate.name << ", Bounty: " << pirate.bounty << " milion berries]";
    return os;
}

void Crew::add(string name, int bounty) {
    Pirate* cur = crewmate;
    if (cur == nullptr) {
        crewmate = new Pirate(name, bounty);
        return;
    }
    if (cur->next != nullptr) {cur = cur->next;}
    cur->next = new Pirate(name, bounty);
    return;
}

void Crew::printCrew() {
    cout << "Crew's Name: " << name << endl;
    cout << "Crew's Member: {" << endl;
    Pirate* cur = crewmate;
    while (cur != nullptr) {
        cout << *cur << endl;
        cur = cur->next;
    }
    cout << "}" << endl;
}

Crew* formAlliance(Crew* crew1, Crew* crew2) {
    if (crew1->crewmate == nullptr && crew2->crewmate == nullptr) {
        cout << "Can't form an Alliance!";
        return nullptr;
    }
    else if (crew1->crewmate == nullptr) {return crew2;}
    else if (crew2->crewmate == nullptr) {return crew1;}

    Pirate* head = new Pirate("", 0);
    Pirate* tail = head;
    Pirate* cur1 = crew1->crewmate;
    Pirate* cur2 = crew2->crewmate;

    while (!(cur1 == nullptr && cur2 == nullptr)) {
        if (cur1 == nullptr || cur1->bounty < cur2->bounty) {
            tail->next = new Pirate(cur2->name, cur2->bounty);
            cur2 = cur2->next;
        }
        else {
            tail->next = new Pirate(cur1->name, cur1->bounty);
            cur1 = cur1->next;
        }
        tail = tail->next;
    }

    string name = crew1->name + "-" + crew2->name + " Alliance";
    return new Crew(name, head->next);
}

Pirate::Pirate(string name, int bounty) {
    this->name = name;
    this->bounty = bounty;
    this->next = nullptr;
}

Crew::Crew(string name, Pirate* captain) {
    this->name = name;
    this->crewmate = captain;
}

int main() {    
    cout << "============== TEST 1 (Toán tử <<) ==============" << endl;
    Pirate* luffy = new Pirate("Luffy", 3000);
    Pirate* law = new Pirate("Law", 3000);

    cout << *law << endl;
    cout << *luffy << endl;


    cout << "\n============== TEST 2 (Crew add & print) ==============" << endl;
    Crew* strawhatPirate = new Crew("Strawhat Pirates", luffy);
    
    strawhatPirate->add("Zoro", 1150);
    strawhatPirate->add("Sanji", 1032);
    strawhatPirate->printCrew();


    cout << "\n============== TEST 3 (formAlliance Bình thường) ==============" << endl;
    Crew* heartPirate = new Crew("Heart Pirates", law);
    heartPirate->add("Jean Bart", 1150); // Cùng bounty với Zoro để test luật ai xuất hiện trước
    heartPirate->add("Bepo", 500);

    Crew* alliance = formAlliance(strawhatPirate, heartPirate);
    if (alliance != nullptr) {
        alliance->printCrew();
    }


    cout << "\n============== TEST 4 (formAlliance Các trường hợp đặc biệt) ==============" << endl;
    Crew* emptyCrew1 = new Crew("Empty1", nullptr);
    Crew* emptyCrew2 = new Crew("Empty2", nullptr);

    // Test 1: Cả 2 crew đều không có thành viên
    cout << "> Test 2 crew trong:" << endl;
    formAlliance(emptyCrew1, emptyCrew2); // Đợi in ra: "Can't form an Alliance!"

    // Test 2: Một trong 2 crew không có thành viên
    cout << "\n> Test 1 crew trong kết hợp 1 crew có người:" << endl;
    Crew* halfAlliance = formAlliance(emptyCrew1, strawhatPirate);
    if (halfAlliance != nullptr) halfAlliance->printCrew(); // Chỉ in ra team Strawhat

    return 0;
}