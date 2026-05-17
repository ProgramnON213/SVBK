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

    // 1. TODO: Append a pirate to the end of the array
    void append(string name, int bounty) {
        if (size == capacity) {
            capacity *= 2; // Double the capacity
            Pirate* newCrewmate = new Pirate[capacity];
            
            // Copy existing members
            for (int i = 0; i < size; ++i) {
                newCrewmate[i] = crewmate[i];
            }
            
            delete[] crewmate; // Free old memory
            crewmate = newCrewmate; // Point to new array
        }
        
        // Add new pirate at the end
        crewmate[size] = Pirate(name, bounty);
        size++;
    }

    // 2. TODO: Prepend a pirate to the beginning of the array
    void prepend(string name, int bounty) {
        if (size == capacity) {
            capacity *= 2; // Double the capacity
        }
        
        Pirate* newCrewmate = new Pirate[capacity];
        
        // Place new pirate at the beginning
        newCrewmate[0] = Pirate(name, bounty);
        
        // Shift existing members to the right
        for (int i = 0; i < size; ++i) {
            newCrewmate[i + 1] = crewmate[i];
        }
        
        delete[] crewmate; // Free old memory
        crewmate = newCrewmate; // Point to new array
        size++;
    }

    friend Crew* formAlliance(Crew* crew1, Crew* crew2);
};

// 3. TODO: Form an alliance between two crews
Crew* formAlliance(Crew* crew1, Crew* crew2) {
    // Both crews empty
    if (crew1->size == 0 && crew2->size == 0) {
        cout << "Can't form an Alliance!" << endl;
        return nullptr;
    }
    
    // One crew empty
    if (crew1->size == 0) return crew2;
    if (crew2->size == 0) return crew1;

    // Create the new alliance crew
    // (Following the text rule: <crew1Name>-<crew2Name> Alliance)
    string allianceName = crew1->name + "-" + crew2->name + " Alliance";
    
    // Create new crew with enough capacity to hold everyone
    Crew* alliance = new Crew(allianceName, crew1->size + crew2->size);

    // 1. Add all members from crew1 first (maintaining order)
    for (int i = 0; i < crew1->size; ++i) {
        alliance->append(crew1->crewmate[i].name, crew1->crewmate[i].bounty);
    }

    // 2. Merge members from crew2
    for (int i = 0; i < crew2->size; ++i) {
        string pName = crew2->crewmate[i].name;
        int pBounty = crew2->crewmate[i].bounty;
        bool found = false;

        // Check if pirate already exists in the alliance
        for (int j = 0; j < alliance->size; ++j) {
            if (alliance->crewmate[j].name == pName) {
                found = true;
                // Keep the higher bounty
                if (pBounty > alliance->crewmate[j].bounty) {
                    alliance->crewmate[j].bounty = pBounty;
                }
                break;
            }
        }

        // If not found in crew1, append them to the alliance
        if (!found) {
            alliance->append(pName, pBounty);
        }
    }

    return alliance;
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