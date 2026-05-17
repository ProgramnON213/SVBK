#include <iostream>
#include <string>

using namespace std;

class Crew;
class Pirate {
public:
    string name;
    int bounty;

    // Default constructor
    Pirate() {
        this->name = "";
        this->bounty = 0;
    }

    // Parameterized constructor
    Pirate(string name, int bounty) {
        this->name = name;
        this->bounty = bounty;
    }

    // Overload operator<< for printing
    friend ostream& operator<<(ostream& os, const Pirate& pirate) {
        os << "Pirate: " << pirate.name << ", Bounty: " << pirate.bounty << " million Berri";
        return os;
    }

    friend class Crew;
    friend Crew* formAlliance(Crew* crew1, Crew* crew2);
};

class Crew {
public:
    string name;
    Pirate* crewmate;
    int size;
    int capacity;

    // Constructor
    Crew(string name, int capacity = 2) {
        this->name = name;
        this->capacity = capacity;
        this->size = 0;
        this->crewmate = new Pirate[capacity];
    }

    // Destructor to free dynamic memory
    ~Crew() {
        delete[] crewmate;
    }

    // Print crew members
    void printCrew() {
        cout << "Crew: " << name << endl;
        for (int i = 0; i < size; ++i) {
            cout << crewmate[i] << endl;
        }
    }

void append(string name, int bounty); //TODO
void prepend(string name, int bounty); //TODO
friend Crew* formAlliance(Crew* crew1, Crew* crew2); //TODO
};

void Crew::append(string name, int bounty) {
    if (size + 1 > capacity) {
        capacity *= 2;
        Pirate* newCrewmate = new Pirate[capacity];
        for (int i = 0; i < capacity/2; i++) {
            newCrewmate[i] = crewmate[i];
        }
        
        delete[] crewmate;
        
        crewmate = newCrewmate;
    }

    crewmate[size] = Pirate(name, bounty);
    size += 1;
}

void Crew::prepend(string name, int bounty) {
    if (size + 1 > capacity) {
        capacity *= 2;
        Pirate* newCrewmate = new Pirate[capacity];
        for (int i = 0; i < capacity/2; i++) {
            newCrewmate[i] = crewmate[i];
        }
        
        delete[] crewmate;
        
        crewmate = newCrewmate;
    }

    for (int i = 0; i < size; i++) {
        crewmate[size-i] = crewmate[size-i-1];
    }
    crewmate[0] = Pirate(name, bounty);
    size += 1;
}

int findNameInCrew(Pirate* crewmate, int size, string name) {
    for (int i = 0; i < size; i++) {
        if (crewmate[i].name == name) {
            return i;
        }
    }
    return -1;
}

Crew* formAlliance(Crew* crew1, Crew* crew2) {
    if (crew1->size == 0 && crew2->size == 0) {
        cout << "Can't form an Alliance!" << endl;
        return nullptr;
    }
    else if (crew1->size == 0) {return crew2;}
    else if (crew2->size == 0) {return crew1;}

    int totalSize = crew1->size + crew2->size;
    Crew* crew = new Crew("Alliance", totalSize*2);
    crew->crewmate = new Pirate[totalSize*2];
    crew->size = 0;

    for (int i = 0; i < crew1->size; i++) {
        crew->crewmate[i] = crew1->crewmate[i];
        crew->size += 1;
    }

    for (int i = 0; i < crew2->size; i++) {
        int tempIndex = findNameInCrew(crew->crewmate, crew->size, crew2->crewmate[i].name);
        if (tempIndex == -1) {
            crew->crewmate[crew1->size + i - 1] = crew2->crewmate[i];
            crew->size += 1;
        }
        else {
            totalSize -= 1;
            if (crew->crewmate[tempIndex].bounty < crew2->crewmate[i].bounty) {
                crew->crewmate[tempIndex] = crew2->crewmate[i];
            }
        }
    }

    return crew;
}

int main() {
    // ---------------------------------------------------------
    // Test 1 (From Example 1)
    // ---------------------------------------------------------
    Pirate* luffy = new Pirate("Luffy", 3000);
    Pirate* law = new Pirate("Law", 3000);

    cout << *law << endl;
    cout << *luffy << endl;
    
    cout << "\n=======================================\n\n";

    // ---------------------------------------------------------
    // Test 2 (From Example 2)
    // ---------------------------------------------------------
    Crew* StrawhatPirate1 = new Crew("Strawhat Pirates");
    StrawhatPirate1->append("Zoro", 1150);
    StrawhatPirate1->append("Sanji", 1032);
    StrawhatPirate1->printCrew();

    cout << "\n=======================================\n\n";

    // ---------------------------------------------------------
    // Test 3 (From Example 3)
    // ---------------------------------------------------------
    Crew* StrawhatPirate2 = new Crew("Strawhat Pirates");
    Crew* HeartPirate = new Crew("Heart Pirates");

    StrawhatPirate2->prepend("Luffy", 3000);
    StrawhatPirate2->prepend("Zoro", 1150);
    StrawhatPirate2->prepend("Sanji", 1032);

    HeartPirate->prepend("Law", 2000);
    HeartPirate->prepend("Bepo", 100);
    HeartPirate->prepend("Sanji", 4000);

    StrawhatPirate2->printCrew();
    HeartPirate->printCrew();

    cout << "------------Form Alliance------------\n";
    
    Crew* alliance = formAlliance(StrawhatPirate2, HeartPirate);
    if (alliance != nullptr) {
        alliance->printCrew();
    }

    // Memory cleanup
    delete luffy;
    delete law;
    delete StrawhatPirate1;
    delete StrawhatPirate2;
    delete HeartPirate;
    delete alliance;

    return 0;
}
