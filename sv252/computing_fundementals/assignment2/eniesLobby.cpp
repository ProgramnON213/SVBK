#include "eniesLobby.h"

/*
 * BattleContext
 */
BattleContext::BattleContext() {
    turnCount = 0;
    morale = 0;
    alarmLevel = 0;
    rescueProgress = 0;
    escapeProgress = 0;
    busterCallTimer = 0;
    mainGateDestroyed = false;
    robinRescued = false;
    bridgeOpened = false;
    battleEnded = false;
    resultCode = "";
}

void BattleContext::nextTurn() {
    // TODO: implement
    turnCount++;
}

void BattleContext::defaultMoraleIncrease() {
    setMorale(this->morale + 5);
}

void BattleContext::setMorale(int morale) {
    this->morale = setByCondition(morale);
};

void BattleContext::setAlarmLevel(int alarmLevel) {
    this->alarmLevel = setByCondition(alarmLevel);
}

void BattleContext::setRescueProgress(int rescueProgress) {
    this->rescueProgress = setByCondition(rescueProgress);
}

void BattleContext::setEscapeProgress(int escapeProgress) {
    this->escapeProgress = setByCondition(escapeProgress);
};
    
void BattleContext::setBusterCallTimer(int busterCallTimer) {
    if (busterCallTimer < 0) {
        this->busterCallTimer = 0;
    }
    else {
        this->busterCallTimer = busterCallTimer;
    }
};

/*
 * Character
 */
Character::Character() {
    name = "";
    hp = 0;
    maxHp = 0;
    atk = 0;
    def = 0;
    speed = 0;
    energy = 0;
    alive = false;
    killInTurn = false;
}

Character::Character(string name, int hp, int atk, int def, int speed, int energy) {
    // TODO: implement
    setName(name);
    this->maxHp = hp;
    setHP(hp);
    this->atk = atk;
    this->def = def;
    this->speed = speed;
    setEnergy(energy);
    killInTurn = false;
}

Character::~Character() {
    // TODO: implement if needed
}

int Character::attack(Building* target, BattleContext& context) {
    return 0;
}

int Character::specialSkill(Building* target, BattleContext& context) {
    return 0;
}

void Character::endTurn(BattleContext& context) {
    return ;
}

void Character::receiveDamage(int damage) {
    // TODO: implement
    int realDamage = damage - this->def;
    if (realDamage > 0) {
        setHP(this->hp - realDamage);
    }
}

bool Character::isAlive() const {
    // TODO: implement
    bool alive = this->alive;
    return alive;
}

string Character::getName() const {
    // TODO: implement
    string name = this->name;
    return name;
}

void Character::setName(string name) {
    this->name = name;
}

int Character::getHP() const {
    // TODO: implement
    int hp = this->hp;
    return hp;
}

int Character::getMaxHP() const {
    return this->maxHp;
}

void Character::setHP(int hp) {
    this->hp = setByCondition(hp, 0, maxHp);
    this->alive = (this->hp == 0);
}

int Character::getEnergy() const {
    // TODO: implement
    int energy = this->energy;
    return energy;
}

void Character::setEnergy(int energy) {
    this->energy = setByCondition(energy);
}

int Character::getDef() const {
    return def;
}

void Character::setDef(int def) {
    this->def = def;
}

int Character::getSpeed() const {
    return speed;
}
void Character::setSpeed(int speed) {
    this->speed = speed;
}

bool Character::isStrawHat() const {
    return false;
}

bool Character::isCP9() const {
    return false;
}

string Character::strCharacter() const {
    stringstream res;
    res << "name=" << this->name << ", hp=" << this->hp << ", atk=" << this->atk << ", def=" << this->def <<", speed=" << this->speed << ", energy=" << this->energy;
    return res.str();
}

/*
 * StrawHat
 */
StrawHat::StrawHat() : Character() {
    bounty = 0;
}

StrawHat::StrawHat(string name, int hp, int atk, int def,
                   int speed, int energy, long long bounty) : Character(name, hp, atk, def, speed, energy) {
    // TODO: implement
    this->bounty = bounty;
}

bool StrawHat::isStrawHat() const {
    // TODO: implement
    return true;
}

string StrawHat::str() const {
    // TODO: implement
    stringstream res;
    res << "StrawHat [" << this->strCharacter() << ", bounty=" << this->bounty << "]";
    return res.str();
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) { 
    // TODO: implement
}

int Luffy::calculateAttackDamge() const {
    int damage = atk;
    int halfHP = ceil(0.5 * hp);
    int lowHP = ceil(0.3 * hp);
    if (hp <= halfHP && hp > lowHP) {
        damage = ceil(damage*1.15);
    }
    else if (hp <= lowHP) {
        damage = ceil(damage*1.3);
    }
    return damage;
}

int Luffy::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = calculateAttackDamge();

    target->receiveDamage(damage);

    if (!target->isAlive()) {
        context.setMorale(context.morale + 5);
    }

    return damage;
}

int Luffy::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = calculateAttackDamge();

    target->receiveDamage(damage);

    if (target->isDestroyed()) {
        context.setMorale(context.morale + 5);
    }

    return damage;
}

int Luffy::calculateSkillDamage(BattleContext& context) {
    int damage = 2 * atk + 15;
    setEnergy(energy - 20);
    speed += 15;
    context.setAlarmLevel(context.alarmLevel + 10);
    int lostHp = ceil(0.08*maxHp);
    setHP(hp - lostHp);
    return damage;
}

int Luffy::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = calculateSkillDamage(context);

    target->receiveDamage(damage);

    return damage;
}

int Luffy::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = calculateSkillDamage(context);

    target->receiveDamage(damage);

    return damage;
}

void Luffy::endTurn(BattleContext& context) {
    // TODO: implement
    if (killInTurn) {
        setEnergy(energy + 5);
    }
    if (hp <= ceil(0.3*maxHp)) {
        context.setMorale(context.morale + 3);
    }
}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Zoro::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = atk + ceil(0.2 * def);
    if (target->getHP() < ceil(0.4 * target->getMaxHP())) {
        damage = ceil(1.15 * damage);
    }

    target->receiveDamage(damage);

    return damage;
}

int Zoro::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = atk + ceil(0.2 * def);
    if (target->getHP() < ceil(0.4 * target->getMaxHP())) {
        damage = ceil(1.15 * damage);
    }

    target->receiveDamage(damage);

    return damage;
}

int Zoro::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(2.2 * atk);
    if (target->getHP() < ceil(0.5) * target->getMaxHP()) {
        damage = ceil(1.5 * damage);
    }

    target->receiveDamage(damage);

    if (!(target->isAlive())) {
        setEnergy(energy + 8);
        context.setMorale(context.morale + 4);
    }
    return damage;
}

int Zoro::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(2.2 * atk);
    if (target->getHP() < ceil(0.5) * target->getMaxHP()) {
        damage = ceil(1.5 * damage);
    }

    target->receiveDamage(damage);

    if ((target->isDestroyed())) {
        setEnergy(energy + 8);
        context.setMorale(context.morale + 4);
    }
    return damage;
}

void Zoro::endTurn(BattleContext& context) {
    // TODO: implement
    if (killInTurn) {
        context.setMorale(context.morale + 6);
        atk = ceil(1.05 * atk);
    }
}

/*
 * Sanji
 */
Sanji::Sanji(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Sanji::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = atk + ceil(0.5*speed);
    if (target->getDef() < def) {
        damage = ceil(damage * 1.1);
    }

    target->receiveDamage(damage);

    return damage;
}

int Sanji::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = atk + ceil(0.5*speed);

    target->receiveDamage(damage);

    return damage;
}

int Sanji::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(2.1 * atk);

    target->receiveDamage(damage);

    if (target->getName() == "JABRA") {
        target->setDef(target->getDef() - 12);
    }
    else {
        target->setDef(target->getDef() - 8);
    }

    return damage;
}

int Sanji::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(2.1 * atk);

    target->receiveDamage(damage);

    return damage;
}

void Sanji::endTurn(BattleContext& context) {
    // TODO: implement
    if (killInTurn) {
        context.setMorale(context.morale + 8);
        atk = ceil(1.1 * atk);
    }
}

/*
 * Nami
 */
Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Nami::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = atk;

    int tempDef = target->getDef();
    target->setDef(ceil(0.7 * target->getDef()));
    target->receiveDamage(damage);
    target->setDef(tempDef);

    return damage;
}

int Nami::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(0.5*atk);

    target->receiveDamage(damage);

    return damage;
}

void Nami::skillEffect(BattleContext& context) const {
    context.setBusterCallTimer(context.busterCallTimer + 1);
    context.setAlarmLevel(context.alarmLevel - 5);
}

int Nami::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = atk + 40;

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 10);

    skillEffect(context);

    return damage;
}

int Nami::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = (atk + 40);
    damage = ceil(1.5 * damage);

    target->receiveDamage(damage);

    skillEffect(context);

    return damage;
}

void Nami::endTurn(BattleContext& context) {
    // TODO: implement
    if (killInTurn) {
        setEnergy(energy + 6);
    }
    context.setMorale(context.morale + 5);
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Chopper::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = atk;

    target->receiveDamage(damage);

    return damage;
}

int Chopper::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = atk;

    target->receiveDamage(damage);

    return damage;
}

int Chopper::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int heal = 35 + ceil(0.5 * atk);

    target->setHP(target->getHP() + heal);
    if (target->getName() == "LUFFY") {
        context.setMorale(context.morale + 5);
    }

    return heal;
}

void Chopper::endTurn(BattleContext& context) {
    // TODO: implement
    context.setMorale(context.morale + 5);
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Usopp::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = atk;
    if (target->getSpeed() < 50) {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);

    return damage;
}

int Usopp::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(0.5 * atk);

    target->receiveDamage(damage);

    return damage;
}

int Usopp::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(0.8 * atk);

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 12);

    context.setEscapeProgress(context.escapeProgress + 8);

    return damage;
}

int Usopp::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(0.8 * atk);

    target->receiveDamage(damage);

    context.setEscapeProgress(context.escapeProgress + 8);

    return damage;
}

void Usopp::endTurn(BattleContext& context) {
    // TODO: implement
    context.setMorale(context.morale + 10);
}

/*
 * Franky
 */
Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Franky::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(atk + 0.3*def);
    if (target->isCP9()) {
        damage = ceil(1.1 * damage);
    }

    target->receiveDamage(damage);

    return damage;
}

int Franky::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(atk + 0.3*def);

    target->receiveDamage(damage);

    return damage;
}

int Franky::specialSkill1(Character* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(1.8 * damage);
    if (target->getName() == "LUCCI") {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 8);

    return damage;
}

int Franky::specialSkill1(Building* target, BattleContext& context) {
    // TODO: implement
    int damage = ceil(1.8 * damage);
    if (target->getName() == "LUCCI") {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);

    return damage;
}

int Franky::specialSkill2(Character* target, BattleContext& context) {
    int damage = ceil(1.2 * damage);

    target->receiveDamage(damage);

    return damage;
}

int Franky::specialSkill2(Building* target, BattleContext& context) {
    int damage = target->getHP();

    target->receiveDamage(damage);

    return damage;
}

void Franky::endTurn(BattleContext& context) {
    // TODO: implement
    if (hp > ceil(0.7 * maxHp)) {
        setDef(def + 5);
    }
    if (hp < ceil(0.3 * maxHp)) {
        atk = ceil(1.1 * atk);
    }
}

/*
 * CP9Agent
 */
CP9Agent::CP9Agent() : Character() {
    doriki = 0;
}

CP9Agent::CP9Agent(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : Character(name, hp, atk, def, speed, energy) {
    // TODO: implement
    this->doriki = doriki;
}

bool CP9Agent::isCP9() const {
    // TODO: implement
    return true;
}

string CP9Agent::str() const {
    // TODO: implement
    stringstream res;
    res << "CP9 [" << this->strCharacter() << ", doriki=" << this->doriki << "]";
    return res.str();
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
}

int Lucci::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Lucci::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Lucci::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
}

int Kaku::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Kaku::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Kaku::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
}

int Jabra::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Jabra::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Jabra::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement 
}

int Blueno::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Blueno::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Blueno::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
}

int Kalifa::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Kalifa::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Kalifa::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
}

int Kumadori::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Kumadori::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Kumadori::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Fukurou
 */
Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
}

int Fukurou::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Fukurou::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Fukurou::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Building
 */
Building::Building(string name, int hp) {
    // TODO: implement
    this->name = name;
    this->maxHP = hp;
    setHP(hp);
}

Building::~Building() {
    // TODO: implement if needed
}

void Building::receiveDamage(int damage) {
    // TODO: implement
    setHP(getHP() - damage);
}

bool Building::isDestroyed() const {
    // TODO: implement
    bool destroyed = this->destroyed;
    return destroyed;
}

void Building::onDestroyed(BattleContext& context) {
    return ;
}

string Building::getName() const {
    // TODO: implement
    string name = this->name;
    return name;
}

int Building::getHP() const {
    // TODO: implement
    int hp = this->hp;
    return hp;
}

int Building::getMaxHP() const {
    return maxHP;
}

void Building::setHP(int hp) {
    this->hp = setByCondition(hp, 0, this->maxHP);
    this->destroyed = (this->hp == 0);
}

string Building::str() const {
    stringstream res;
    res << "Building [name=" << this->name << ", hp=" << this->hp << ", maxHP=" << this->maxHP << ", destroyed=" << boolalpha << this->destroyed << "]";
    return res.str();
}

/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

void MainGate::applyEffect(BattleContext& context) {
    // TODO: implement
}

void MainGate::onDestroyed(BattleContext& context) {
    // TODO: implement
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext& context) {
    // TODO: implement
}

void Courthouse::onDestroyed(BattleContext& context) {
    // TODO: implement
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext& context) {
    // TODO: implement
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext& context) {
    // TODO: implement
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext& context) {
    // TODO: implement
}

void BusterCallShip::onDestroyed(BattleContext& context) {
    // TODO: implement
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string& filename) {
    // TODO: implement
}

EniesLobbyBattle::~EniesLobbyBattle() {
    // TODO: implement
}

void EniesLobbyBattle::loadFromFile(const string& filename) {
    // TODO: implement
}

void EniesLobbyBattle::addStrawHat(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::addCP9Agent(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::addBuilding(Building* building) {
    // TODO: implement
}

void EniesLobbyBattle::buildTurnOrder() {
    // TODO: implement
}

void EniesLobbyBattle::runBattle() {
    // TODO: implement
}

void EniesLobbyBattle::processTurn(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::processBuildings() {
    // TODO: implement
}

void EniesLobbyBattle::checkEndCondition() {
    // TODO: implement
}

string EniesLobbyBattle::getResult() const {
    // TODO: implement
    return "";
}

int setByCondition(int n, int min=0, int max=100) {
    if (n < min) {
        return min;
    }
    else if (n > max) {
        return max;
    }
    return n;
}