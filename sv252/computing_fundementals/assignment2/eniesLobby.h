#ifndef ENIES_LOBBY_H
#define ENIES_LOBBY_H

#include "main.h"

class BattleContext;
class Building;
class Character;
struct TurnNode;

int const MAX_STRAW_HAT_COUNT = 7;
int const MAX_CP9_COUNT = 7;
int const MAX_CHARACTER_COUNT = MAX_STRAW_HAT_COUNT + MAX_CP9_COUNT;
int const MAX_BUILDING_COUNT = 5;

/*
 * Character
 */
class Character {
protected:
    string name;
    int hp;
    int maxHp;
    int atk;
    int def;
    int speed;
    int energy;
    int energyRequirement;
    bool alive;
    bool killCharacterInTurn;
    bool destroyBuildingInTurn;
    bool hasMoraleInDescripton;

public:
    Character();
    Character(string name, int hp, int atk, int def, int speed, int energy);
    virtual ~Character();

    virtual int takeTurn(Character* target, BattleContext& context);
    virtual int takeTurn(Building* target, BattleContext& context);

    virtual int attack(Character* target, BattleContext& context) = 0;
    virtual int specialSkill(Character* target, BattleContext& context) = 0;

    virtual int attack(Building* target, BattleContext& context);
    virtual int specialSkill(Building* target, BattleContext& context);

    virtual void endTurn(BattleContext& context);

    void receiveDamage(int damage);
    
    bool isAlive() const;

    string getName() const;
    int getMaxHP() const;
    int getHP() const;
    int getEnergy() const;
    int getDef() const;
    int getSpeed() const;
    int getEnergyRequirement() const;
    bool getkillCharacterInTurn() const;
    bool getDestroyBuildingInTurn() const;
    int gethasMoraleInDescripton() const;

    void setName(string name);
    void setHPandState(int hp);
    void setEnergy(int energy);
    void setDef(int def);
    void setSpeed(int speed);
    void setkillCharacterInTurn(bool value);
    void setDestroyBuildingInTurn(bool value);

    virtual bool isStrawHat() const;
    virtual bool isCP9() const;

    virtual string str() const = 0;
    string strCharacter() const;
};

/*
 * StrawHat
 */
class StrawHat : public Character {
protected:
    long long bounty;

public:
    StrawHat();
    StrawHat(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty);

    virtual int attack(Character* target, BattleContext& context);
    virtual int specialSkill(Character* target, BattleContext& context);

    virtual bool isStrawHat() const;
    virtual string str() const;
};

/*
 * Straw Hat members
 */
class Luffy : public StrawHat {
public:
    Luffy(string name, int hp, int atk, int def,
          int speed, int energy, long long bounty);

    int takeTurn(Character* target, BattleContext& context);
    int takeTurn(Building* target, BattleContext& context);

    int calculateAttackDamge() const;          
    int attack(Character* target, BattleContext& context);
    int attack(Building* target, BattleContext& context);

    int calculateSkillDamage(BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
};

class Zoro : public StrawHat {
public:
    Zoro(string name, int hp, int atk, int def,
         int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int attack(Building* target, BattleContext& context);

    int specialSkill(Character* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
};

class Sanji : public StrawHat {
public:
    Sanji(string name, int hp, int atk, int def,
          int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
};

class Nami : public StrawHat {
public:
    Nami(string name, int hp, int atk, int def,
         int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int attack(Building* target, BattleContext& context);

    void skillEffect(BattleContext& context) const;
    int specialSkill(Character* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
};

class Chopper : public StrawHat {
public:
    Chopper(string name, int hp, int atk, int def,
            int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int attack(Building* target, BattleContext& context);

    int specialSkill(Character* target, BattleContext& context);
    //int specialSkill(Building* target, BattleContext& context); Cannot affect building

    void endTurn(BattleContext& context);
};

class Usopp : public StrawHat {
public:
    Usopp(string name, int hp, int atk, int def,
          int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
};

class Franky : public StrawHat {
public:
    Franky(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty);

    int takeTurn(Character* target, BattleContext& context);
    int takeTurn(Building* target, BattleContext& context);
    
    int attack(Character* target, BattleContext& context);
    int attack(Building* target, BattleContext& context);

    int specialSkill(Character* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);
    int specialSkill1(Character* target, BattleContext& context);
    int specialSkill1(Building* target, BattleContext& context);
    int specialSkill2(Character* target, BattleContext& context);
    int specialSkill2(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
};

/*
 * CP9Agent
 */
class CP9Agent : public Character {
protected:
    int doriki;

public:
    CP9Agent();
    CP9Agent(string name, int hp, int atk, int def,
             int speed, int energy, int doriki);

    virtual bool isCP9() const;
    virtual string str() const;

    virtual int attack(Character* target, BattleContext& context);
    virtual int specialSkill(Character* target, BattleContext& context);
};

/*
 * CP9 members
 */
class Lucci : public CP9Agent {
public:
    Lucci(string name, int hp, int atk, int def,
          int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

class Kaku : public CP9Agent {
public:
    Kaku(string name, int hp, int atk, int def,
         int speed, int energy, int doriki);

    //int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

class Jabra : public CP9Agent {
public:
    Jabra(string name, int hp, int atk, int def,
          int speed, int energy, int doriki);

    //int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

class Blueno : public CP9Agent {
public:
    Blueno(string name, int hp, int atk, int def,
           int speed, int energy, int doriki);

    //int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

class Kalifa : public CP9Agent {
public:
    Kalifa(string name, int hp, int atk, int def,
           int speed, int energy, int doriki);

    //int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

class Kumadori : public CP9Agent {
public:
    Kumadori(string name, int hp, int atk, int def,
             int speed, int energy, int doriki);

    //int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

class Fukurou : public CP9Agent {
public:
    Fukurou(string name, int hp, int atk, int def,
            int speed, int energy, int doriki);

    Character* lowestHPStrawHat;    

    //int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
};

/*
 * BattleContext
 */
class BattleContext {
public:
    int turnCount;
    int morale;
    int alarmLevel;
    int rescueProgress;
    int escapeProgress;
    int busterCallTimer;
    bool mainGateDestroyed;
    bool robinRescued;
    bool bridgeOpened;
    bool battleEnded;
    string resultCode;

public:
    BattleContext();
    BattleContext(int morale, int alarmLevel, int rescueProgress, 
                int escapeProgress, int busterCallTimer);
    void nextTurn();
    void setMorale(int morale);
    void setAlarmLevel(int alarmLevel);
    void setRescueProgress(int rescueProgress);
    void setEscapeProgress(int escapeProgress);
    void setBusterCallTimer(int busterCallTimer);

    void logContext() const;
};

/*
 * Building
 */
class Building {
protected:
    string name;
    int hp;
    int maxHP;
    bool destroyed;

public:
    Building(string name, int hp);
    virtual ~Building();

    void receiveDamage(int damage);
    void takeDamge(int damage, BattleContext& context);
    bool isDestroyed() const;

    virtual void applyEffect(BattleContext& context) = 0;
    virtual void onDestroyed(BattleContext& context);
    
    virtual string str () const;

    string getName() const;
    int getHP() const;
    int getMaxHP() const;

    void setHPandState(int hp);
};

/*
 * Building subclasses
 */
class MainGate : public Building {
public:
    MainGate(string name, int hp);

    void applyEffect(BattleContext& context);
    void onDestroyed(BattleContext& context);
};

class Courthouse : public Building {
public:
    Courthouse(string name, int hp);

    void applyEffect(BattleContext& context);
    void onDestroyed(BattleContext& context);
};

class TowerOfJustice : public Building {
public:
    TowerOfJustice(string name, int hp);

    void applyEffect(BattleContext& context);
};

class BridgeOfHesitation : public Building {
public:
    BridgeOfHesitation(string name, int hp);

    void applyEffect(BattleContext& context);
};

class BusterCallShip : public Building {
public:
    BusterCallShip(string name, int hp);

    void applyEffect(BattleContext& context);
    void onDestroyed(BattleContext& context);
};

/*
 * TurnNode to create Linked List turn order
 */
struct TurnNode
{
    Character* data;
    TurnNode* next;
};

/*
 * EniesLobbyBattle
 */
class EniesLobbyBattle {
private:
    Character** strawHats;
    int strawHatCount;

    Character** cp9Agents;
    int cp9Count;

    Building** buildings;
    int buildingCount;

    bool battleEnded;
    TurnNode* turnOrder;
    BattleContext context;
    int maxTurns;

public:
    EniesLobbyBattle(const string& filename);
    ~EniesLobbyBattle();

    void loadFromFile(const string& filename);

    StrawHat* createStrawHat(string name, int hp, int atk, int def, int speed, 
    int energy, long long bounty);
    void addStrawHat(Character* character);
    CP9Agent* createCP9Agent(string name, int hp, int atk, int def, int speed, 
        int energy, int doriki);
    void addCP9Agent(Character* character);
    Building* createBuilding(string name, int hp);
    void addBuilding(Building* building);

    void buildTurnOrder();
    void deleteTurnOrder();
    void moveNodeToEnd();

    void runBattle();
    void selectTarget(Character* character, BattleContext& context, 
        Character*& targetCharacter, Building*& targetBuilding);
    void selectTargetStrawHat(Character* character, BattleContext& context, 
        Character*& targetCharacter, Building*& targetBuilding);
    void processTurn(Character* character);
    void processBuildings();
    void checkEndCondition();
    bool isAllStrawHatDead();
    bool isAllCP9AgentDead();

    string getResult() const;
    Character* firstStrawHatAlive() const;
    Character* firstCP9AgentAlive() const;
    Character* lowestHPAliveStrawHat() const;

    Building* findBuildingWithName(string name);
    int findCharacterWithName(string name) const;
    int findIndexBuildingWithName(string name) const;

    void tempLog();
    void tempLogObjects();
    void tempLogTurnNode();
    void tempLogCharacterAndTarget(Character* character, Character* targetCharacter, 
        Building* targetBuilidng);
};


int setByCondition(int n, int min=0, int max=100);
int calculateDamage(int damage, int def);
int multiplyStat(int n, int damage);

#endif
