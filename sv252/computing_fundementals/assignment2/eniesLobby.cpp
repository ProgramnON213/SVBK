#include "eniesLobby.h"
// REMINDER: Add the morale system back
// REMINDER: attack and specialSkill return value should be actual damage
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

BattleContext::BattleContext(int morale, int alarmLevel, int rescueProgress, 
        int escapeProgress, int busterCallTimer) {
    turnCount = 0;
    setMorale(morale);
    setAlarmLevel(alarmLevel);
    setRescueProgress(rescueProgress);
    setEscapeProgress(escapeProgress);
    setBusterCallTimer(busterCallTimer);
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

void BattleContext::logContext() const {
    cout << "Logging context" << endl;
    cout << boolalpha << "turnCount=" << turnCount << ", morale=" << morale << ", alarmLevel=" << alarmLevel << 
    ", rescueProgress=" << rescueProgress << ", escapeProgress=" << escapeProgress <<
    ", busterCallTimer=" << busterCallTimer << ", mainGateDestroyed=" << mainGateDestroyed <<
    ", robinRescued=" << robinRescued << ", bridgeOpened=" << bridgeOpened << 
    ", battleEnded=" << battleEnded << ", resultCode=" << resultCode << endl;
    cout << "Logging context completed" << endl;
}

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
    setHPandState(hp);
    this->atk = atk;
    this->def = def;
    this->speed = speed;
    setEnergy(energy);
    killInTurn = false;
}

Character::~Character() {
    // TODO: implement if needed
}

int Character::takeTurn(Character* target, BattleContext& context) {
    if (energy >= energyRequirement) {
        energy -= energyRequirement;
        return specialSkill(target, context);
    }
    else {
        return attack(target, context);
    }
}

int Character::takeTurn(Building* target, BattleContext& context) {
    if (energy >= energyRequirement) {
        energy -= energyRequirement;
        return specialSkill(target, context);
    }
    else {
        return attack(target, context);
    }
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
        setHPandState(this->hp - realDamage);
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

void Character::setHPandState(int hp) {
    this->hp = setByCondition(hp, 0, maxHp);
    this->alive = !(this->hp == 0);
}

int Character::getEnergy() const {
    // TODO: implement
    int energy = this->energy;
    return energy;
}

void Character::setEnergy(int energy) {
    this->energy = setByCondition(energy);
}

int Character::getEnergyRequirement() const {
    return energyRequirement;
}

int Character::getKillInTurn() const {
    return killInTurn;
}

int Character::getDefaultMoraleChange() const {
    return defaultMoraleChange;
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

void Character::setKillInTurn(bool value) {
    this->killInTurn = value;
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

int StrawHat::attack(Character* target, BattleContext& context) {
    return 0;
}
int StrawHat::specialSkill(Character* target, BattleContext& context) {
    return 0;
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) { 
    // TODO: implement
    energyRequirement = 20;
    defaultMoraleChange = false;
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

int Luffy::takeTurn(Character* target, BattleContext& context) {
    if (energy >= energyRequirement && hp >= ceil(0.15 * maxHp)) {
        energy -= energyRequirement;
        return specialSkill(target, context);
    }
    else {
        return attack(target, context);
    }
}

int Luffy::takeTurn(Building* target, BattleContext& context) {
    if (energy >= energyRequirement && hp >= ceil(0.15 * maxHp)) {
        energy -= energyRequirement;
        return specialSkill(target, context);
    }
    else {
        return attack(target, context);
    }
}

int Luffy::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = calculateAttackDamge();

    target->receiveDamage(damage);

    if (!target->isAlive()) {
        context.setMorale(context.morale + 5);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Luffy::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = calculateAttackDamge();

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Luffy::calculateSkillDamage(BattleContext& context) {
    int damage = 2 * atk + 15;
    setEnergy(energy - 20);
    speed += 15;
    context.setAlarmLevel(context.alarmLevel + 10);
    int lostHp = ceil(0.08*maxHp);
    setHPandState(hp - lostHp);
    return damage;
}

int Luffy::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = calculateSkillDamage(context);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Luffy::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = calculateSkillDamage(context);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
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
    energyRequirement = 15;
    defaultMoraleChange = false;
}

int Zoro::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk + ceil(0.2 * def);
    if (target->getHP() < ceil(0.4 * target->getMaxHP())) {
        damage = ceil(1.15 * damage);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Zoro::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk + ceil(0.2 * def);
    if (target->getHP() < ceil(0.4 * target->getMaxHP())) {
        damage = ceil(1.15 * damage);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Zoro::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(2.2 * atk);
    if (target->getHP() < ceil(0.5) * target->getMaxHP()) {
        damage = ceil(1.5 * damage);
    }

    target->receiveDamage(damage);

    if (!(target->isAlive())) {
        setEnergy(energy + 8);
        context.setMorale(context.morale + 4);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Zoro::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(2.2 * atk);
    if (target->getHP() < ceil(0.5) * target->getMaxHP()) {
        damage = ceil(1.5 * damage);
    }

    target->receiveDamage(damage);
    
    int hp2 = target->getHP();
    return hp1 - hp2;
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
    energyRequirement = 18;
    defaultMoraleChange = false;
}

int Sanji::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk + ceil(0.5*speed);
    if (target->getDef() < def) {
        damage = ceil(damage * 1.1);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Sanji::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk + ceil(0.5*speed);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Sanji::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(2.1 * atk);

    target->receiveDamage(damage);

    if (target->getName() == "JABRA") {
        target->setDef(target->getDef() - 12);
    }
    else {
        target->setDef(target->getDef() - 8);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Sanji::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(2.1 * atk);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
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
    energyRequirement = 20;
    defaultMoraleChange = true;
}

int Nami::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk;

    int tempDef = target->getDef();
    target->setDef(ceil(0.7 * target->getDef()));
    target->receiveDamage(damage);
    target->setDef(tempDef);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Nami::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(0.5*atk);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Nami::skillEffect(BattleContext& context) const {
    context.setBusterCallTimer(context.busterCallTimer + 1);
    context.setAlarmLevel(context.alarmLevel - 5);
}

int Nami::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk + 40;

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 10);

    skillEffect(context);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Nami::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = (atk + 40);
    damage = ceil(1.5 * damage);

    target->receiveDamage(damage);

    skillEffect(context);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Nami::endTurn(BattleContext& context) {
    // TODO: implement
    if (killInTurn) {
        setEnergy(energy + 6);
    }
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
    energyRequirement = 15;
    defaultMoraleChange = false;
}

int Chopper::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk;

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Chopper::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk;

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Chopper::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int heal = 35 + ceil(0.5 * atk);

    target->setHPandState(target->getHP() + heal);
    if (target->getName() == "LUFFY") {
        context.setMorale(context.morale + 5);
    }

    return 0;
}

void Chopper::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
    energyRequirement = 16;
    defaultMoraleChange = false;
}

int Usopp::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk;
    if (target->getSpeed() < 50) {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Usopp::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(0.5 * atk);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Usopp::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(0.8 * atk);

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 12);

    context.setEscapeProgress(context.escapeProgress + 8);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Usopp::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(0.8 * atk);

    target->receiveDamage(damage);

    context.setEscapeProgress(context.escapeProgress + 8);

    int hp2 = target->getHP();
    return hp1 - hp2;
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
    defaultMoraleChange = true;
}

int Franky::takeTurn(Character* target, BattleContext& context) {
    if (energy >= 30) {
        energy -= 30;
        return specialSkill2(target, context);
    }
    else if (energy >= 20) {
        energy -= 20;
        return specialSkill1(target, context);
    }
    else {
        return attack(target, context);
    }
}

int Franky::takeTurn(Building* target, BattleContext& context) {
    if (energy >= 30) {
        energy -= 30;
        return specialSkill2(target, context);
    }
    else if (energy >= 20) {
        energy -= 20;
        return specialSkill1(target, context);
    }
    else {
        return attack(target, context);
    }
}


int Franky::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(atk + 0.3*def);
    if (target->isCP9()) {
        damage = ceil(1.1 * damage);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Franky::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(atk + 0.3*def);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

// REMINDER: May need to implement this
int Franky::specialSkill(Character* target, BattleContext& context) {
    return 0;
}
int Franky::specialSkill(Building* target, BattleContext& context) {
    return 0;
}

int Franky::specialSkill1(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(1.8 * atk);
    if (target->getName() == "LUCCI") {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 8);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Franky::specialSkill1(Building* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(1.8 * atk);
    if (target->getName() == "LUCCI") {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Franky::specialSkill2(Character* target, BattleContext& context) {
    int hp1 = target->getHP();
    int damage = ceil(1.2 * atk);

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Franky::specialSkill2(Building* target, BattleContext& context) {
    int hp1 = target->getHP();
    int damage = target->getHP();

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
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

int CP9Agent::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk;

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int CP9Agent::specialSkill(Character* target, BattleContext& context) {
    return 0;
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
    energyRequirement = 25;
    defaultMoraleChange = false;
}

int Lucci::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = atk + ceil(0.05 * doriki);
    if (target->getHP() < target->getMaxHP()) {
        damage = ceil(1.2 * damage);
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

int Lucci::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(2.8 * atk);

    int tempDef = target->getDef();
    target->setDef(tempDef - ceil(0.5*tempDef));
    target->receiveDamage(damage);
    target->setDef(tempDef);

    if (!target->isAlive()) {
        context.setMorale(context.morale - 10);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Lucci::endTurn(BattleContext& context) {
    // TODO: implement
    if (hp < ceil(0.4 * maxHp)) {
        atk = ceil(1.05 * atk);
    }
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
    energyRequirement = 20;
    defaultMoraleChange = true;
}

int Kaku::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();

    int damage1 = ceil(1.2 * atk);
    target->receiveDamage(damage1);

    if (target->isAlive()) {
        int damage2 = atk;
        target->receiveDamage(damage2);
    }

    if (target->isAlive()) {
        int damage3 = ceil(0.8 * atk);
        target->receiveDamage(damage3);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Kaku::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
    energyRequirement = 18;
    defaultMoraleChange = false;
}

int Jabra::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(1.5 * atk);
    if (hp < ceil(0.3 * maxHp)) {
        damage = ceil(1.25 * damage);
    }

    target->receiveDamage(damage);

    if (!target->isAlive()) {
        context.setMorale(context.morale - 5);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Jabra::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement 
    energyRequirement = 15;
    defaultMoraleChange = true;
}

int Blueno::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(1.3 * atk);
    if (hp > ceil(0.5 * maxHp)) {
        damage += 20;
    }
    else if (hp <= ceil(0.5 * maxHp)) {
        damage += 40;
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Blueno::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
    energyRequirement = 18;
    defaultMoraleChange = false;
}

int Kalifa::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(1.4 * atk);

    target->receiveDamage(damage);
    target->setSpeed(target->getSpeed() - 6);

    if (target->getName() == "NAMI") {
        context.setMorale(context.morale - 12);
    }
    else {
        context.setMorale(context.morale - 8);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Kalifa::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
    energyRequirement = 16;
    defaultMoraleChange = true;
}

int Kumadori::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = 30 + ceil(0.1 * doriki);
    if (hp < ceil(0.4 * maxHp)) {
        damage += 25;
    }

    target->receiveDamage(damage);

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Kumadori::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Fukurou
 */
Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
    // TODO: implement
    energyRequirement = 14;
    defaultMoraleChange = false;
}

int Fukurou::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    int hp1 = target->getHP();
    int damage = ceil(1.3 * atk);
    if (target == lowestHPStrawHat) {
        damage += 20;
    }

    target->receiveDamage(damage);

    if (!target->isAlive()) {
        context.setMorale(context.morale - 6);
    }

    int hp2 = target->getHP();
    return hp1 - hp2;
}

void Fukurou::endTurn(BattleContext& context) {
    // TODO: implement
    ;
}

/*
 * Building
 */
Building::Building(string name, int hp) {
    // TODO: implement
    this->name = name;
    this->maxHP = hp;
    setHPandState(hp);
}

Building::~Building() {
    // TODO: implement if needed
}

void Building::receiveDamage(int damage) {
    // TODO: implement
    setHPandState(getHP() - damage);
}

bool Building::isDestroyed() const {
    // TODO: implement
    bool destroyed = this->destroyed;
    return destroyed;
}

void Building::applyEffect(BattleContext& context) {
    return ;
}

void Building::onDestroyed(BattleContext& context) {
    return ;
}

string Building::getName() const {
    // TODO: implement
    return name;
}

int Building::getHP() const {
    // TODO: implement
    return hp;
}

int Building::getMaxHP() const {
    return maxHP;
}

void Building::setHPandState(int hp) {
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
    // if not destroyed, rescueProgress will not increase in this turn
}

void MainGate::onDestroyed(BattleContext& context) {
    // TODO: implement
    context.mainGateDestroyed = true;
    context.setRescueProgress(context.rescueProgress + 20);
    context.setMorale(context.morale + 5);
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext& context) {
    // TODO: implement
    context.setAlarmLevel(context.alarmLevel + 5);
}

void Courthouse::onDestroyed(BattleContext& context) {
    // TODO: implement
    context.setAlarmLevel(context.alarmLevel - 20);
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext& context) {
    // TODO: implement
    if (context.mainGateDestroyed && !context.robinRescued) {
        context.setRescueProgress(context.rescueProgress + 5);
    }
    if (context.rescueProgress >= 100) {
        context.robinRescued = true;
        context.setMorale(context.morale + 10);
    }
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext& context) {
    // TODO: implement
    if (context.robinRescued) {
        context.bridgeOpened = true;
        context.setEscapeProgress(context.escapeProgress + 5);
    }
    if (context.escapeProgress >= 100) {
        // Fight end with STAW_HAT_WIN
    }
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext& context) {
    // TODO: implement
    if (!isDestroyed()) {
        context.setBusterCallTimer(context.busterCallTimer - 1);
    }
    if (context.busterCallTimer <= 0) {
        // Fight end with BUSTER CALL
        context.battleEnded = true;
        context.resultCode = "BUSTER CALL";
    }
}

void BusterCallShip::onDestroyed(BattleContext& context) {
    // TODO: implement
    context.setBusterCallTimer(context.busterCallTimer + 3);
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string& filename) {
    // TODO: implement
    strawHats = new Character* [MAX_STRAW_HAT_COUNT];
    strawHatCount = 0;
    
    cp9Agents = new Character* [MAX_CHARACTER_COUNT];
    cp9Count = 0;

    buildings = new Building* [MAX_BUILDING_COUNT];
    buildingCount = 0;

    battleEnded = false;

    loadFromFile(filename);
}

EniesLobbyBattle::~EniesLobbyBattle() {
    // TODO: implement
    for (int i = 0; i < MAX_STRAW_HAT_COUNT; i++) {
        delete strawHats[i];
    }
    delete[] strawHats;

    for (int i = 0; i < MAX_CP9_COUNT; i++) {
        delete cp9Agents[i];
    }
    delete[] cp9Agents;

    for (int i = 0; i < MAX_BUILDING_COUNT; i++) {
        delete buildings[i];
    }
    delete[] buildings;

    deleteTurnOrder();
}

void EniesLobbyBattle::loadFromFile(const string& filename) {
    // TODO: implement
    ifstream f(filename);
    if (!f.is_open()) {return;}
    string line;
    while (getline(f, line)) {
        stringstream stream(line);
        string lineObjectType;
        stream >> lineObjectType;

        if (lineObjectType == "CONTEXT") {
            int morale, alarmLevel, rescueProgress, escapeProgress, busterCallTimer, maxTurns;
            stream >> morale >> alarmLevel >> rescueProgress >> escapeProgress >> busterCallTimer >> maxTurns;
            this->maxTurns = maxTurns;
            BattleContext context = BattleContext(morale, alarmLevel, rescueProgress, escapeProgress, busterCallTimer);
        }
        
        else if (lineObjectType == "STRAW_HAT") {
            string name;
            int hp, atk, def, speed, energy;
            long long bounty;
            stream >> name >> hp >> atk >> def >> speed >> energy >> bounty;

            StrawHat* pirate = createStrawHat(name, hp, atk, def, speed, energy, bounty);
            addStrawHat(pirate);
        }

        else if (lineObjectType == "CP9") {
            string name;
            int hp, atk, def, speed, energy, doriki;
            stream >> name >> hp >> atk >> def >> speed >> energy >> doriki;

            CP9Agent* agent = createCP9Agent(name, hp, atk, def, speed, energy, doriki);
            addCP9Agent(agent);
        }

        else if (lineObjectType == "BUILDING") {
            string name;
            int hp;
            stream >> name >> hp;

            Building* building = createBuilding(name, hp);
            addBuilding(building);
        }
    }

    buildTurnOrder();
}

StrawHat* EniesLobbyBattle::createStrawHat(string name, int hp, int atk, int def, int speed, 
    int energy, long long bounty) {
    StrawHat* pirate = nullptr;
    if (name == "Luffy") {
        pirate = new Luffy(name, hp, atk, def, speed, energy, bounty);
    }
    else if (name == "Zoro") {
        pirate = new Zoro(name, hp, atk, def, speed, energy, bounty);
    }
    else if (name == "Sanji") {
        pirate = new Sanji(name, hp, atk, def, speed, energy, bounty);
    }
    else if (name == "Nami") {
        pirate = new Nami(name, hp, atk, def, speed, energy, bounty);
    }
    else if (name == "Chopper") {
        pirate = new Chopper(name, hp, atk, def, speed, energy, bounty);
    }
    else if (name == "Usopp") {
        pirate = new Usopp(name, hp, atk, def, speed, energy, bounty);
    }
    else if (name == "Franky") {
        pirate = new Franky(name, hp, atk, def, speed, energy, bounty);
    }
    else {
        pirate = nullptr;
    }
    return pirate;
}

void EniesLobbyBattle::addStrawHat(Character* character) {
    // TODO: implement
    strawHats[strawHatCount] = character;
    strawHatCount++;
}

CP9Agent* EniesLobbyBattle::createCP9Agent(string name, int hp, int atk, int def, int speed, 
    int energy, int doriki) {
    CP9Agent* agent = nullptr;
    if (name == "Lucci") {
        agent = new Lucci(name, hp, atk, def, speed, energy, doriki);
    }
    else if (name == "Kaku") {
        agent = new Kaku(name, hp, atk, def, speed, energy, doriki);
    }
    else if (name == "Jabra") {
        agent = new Jabra(name, hp, atk, def, speed, energy, doriki);
    }
    else if (name == "Blueno") {
        agent = new Blueno(name, hp, atk, def, speed, energy, doriki);
    }
    else if (name == "Kalifa") {
        agent = new Kalifa(name, hp, atk, def, speed, energy, doriki);
    }
    else if (name == "Kumadori") {
        agent = new Kumadori(name, hp, atk, def, speed, energy, doriki);
    }
    else if (name == "Fukurou") {
        agent = new Fukurou(name, hp, atk, def, speed, energy, doriki);
    }
    else {
        agent = nullptr;
    }
    return agent;
}

void EniesLobbyBattle::addCP9Agent(Character* character) {
    // TODO: implement
    cp9Agents[cp9Count] = character;
    cp9Count++;
}

Building* EniesLobbyBattle::createBuilding(string name, int hp) {
    Building* building = nullptr;
    if (name == "MainGate") {
        building = new MainGate(name, hp);
    }
    else if (name == "Courthouse") {
        building = new Courthouse(name, hp);
    }
    else if (name == "TowerOfJustice") {
        building = new TowerOfJustice(name, hp);
    }
    else if (name == "BridgeOfHesitation") {
        building = new BridgeOfHesitation(name, hp);
    }
    else if (name == "BusterCallShip") {
        building = new BusterCallShip(name, hp);
    }
    else {
        building = nullptr;
    }
    return building;
}

void EniesLobbyBattle::addBuilding(Building* building) {
    // TODO: implement
    buildings[buildingCount] = building;
    buildingCount++;
}

void EniesLobbyBattle::buildTurnOrder() {
    // TODO: implement
    turnOrder = nullptr;
    TurnNode* tail = turnOrder;

    for (int i = 0; i < strawHatCount; i++) {
        TurnNode* newNode = new TurnNode;
        newNode->data = strawHats[i];
        newNode->next = nullptr;
        if (turnOrder == nullptr) {
            turnOrder = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    for (int i = 0; i < cp9Count; i++) {
        TurnNode* newNode = new TurnNode;
        newNode->data = cp9Agents[i];
        newNode->next = nullptr;
        if (turnOrder == nullptr) {
            turnOrder = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }
}

void EniesLobbyBattle::deleteTurnOrder() {
    TurnNode* current = turnOrder;
    while (current != nullptr) {
        TurnNode* next = turnOrder->next;
        delete current;
        current = next;
    }
}

void EniesLobbyBattle::moveNodeToEnd() {
    if (turnOrder == nullptr || turnOrder->next == nullptr) {return;}
    
    TurnNode* temp = turnOrder;

    TurnNode* current = turnOrder;
    while (current->next != nullptr) {
        current = current->next;
    }
    turnOrder = turnOrder->next;

    current->next = temp;
    current->next->next = nullptr;
}

void EniesLobbyBattle::runBattle() {
    // TODO: implement
    while (!battleEnded) {
        if (turnOrder->data->isAlive()) {
            Character* character = turnOrder->data;
            processTurn(character); // Bug here
        }
        
        moveNodeToEnd();

        processBuildings();

        context.nextTurn();

        checkEndCondition();

        tempLogTurnNode();
        tempLogObjects();
    }
}

void EniesLobbyBattle::selectTarget(Character* character, BattleContext& context, 
    Character*& targetCharacter, Building*& targetBuilding) {
    targetCharacter = nullptr;
    targetBuilding = nullptr;
    
    if (character->isStrawHat()) {
        selectTargetStrawHat(character, context, targetCharacter, targetBuilding);
    }
    else if (character->isCP9()) {
        targetCharacter = firstStrawHatAlive();
    }
}

void EniesLobbyBattle::selectTargetStrawHat(Character* character, BattleContext& context, 
    Character*& targetCharacter, Building*& targetBuilding) {
        if (character->getName() == "Chopper" && character->getEnergy() >= character->getEnergyRequirement()) {
            targetCharacter = lowestHPCharacterInStrawHat();
        }
        else if (!context.mainGateDestroyed) {
            targetBuilding = findBuildingWithName("MainGate");
        }
        else if (context.alarmLevel >= 50 && !findBuildingWithName("Courthouse")->isDestroyed()) {
            targetBuilding = findBuildingWithName("Courthouse");
        }
        else if (context.busterCallTimer <= 5 && !findBuildingWithName("BusterCallShip")->isDestroyed()) {
            targetBuilding = findBuildingWithName("BusterCallShip");
        }
        else if (!context.robinRescued) {
            targetCharacter = firstCP9AgentAlive();
        }
        else if (context.robinRescued) {
            targetBuilding = findBuildingWithName("BridgeOfHesitation");
            if (targetBuilding->isDestroyed()) {
                targetCharacter = firstCP9AgentAlive();
                targetBuilding = nullptr;
            }
        }
    }

void EniesLobbyBattle::processTurn(Character* character) {
    // TODO: implement
    Character* targetCharacter; Building* targetBuilding;
    selectTarget(character, context, targetCharacter, targetBuilding);
    character->setKillInTurn(false);
    if (character->getName() == "Fukurou") {
        Fukurou* fukurouPtr = (Fukurou*) character;
        fukurouPtr->lowestHPStrawHat = lowestHPCharacterInStrawHat();
    }

    if (targetCharacter != nullptr) {
        character->takeTurn(targetCharacter, context);
        if (!targetCharacter->isAlive()) {
            character->setKillInTurn(true);
        }
    }
    else if (targetBuilding != nullptr) {
        character->takeTurn(targetBuilding, context);
        if (targetBuilding->isDestroyed()) {
            targetBuilding->onDestroyed(context);
        }
    }

    if (character->getKillInTurn() && character->getDefaultMoraleChange()) {
        if (character->isStrawHat()) {context.setMorale(context.morale + 5);}
        else if (character->isCP9()) {context.setMorale(context.morale - 5);}
    }

    character->endTurn(context);
}

void EniesLobbyBattle::processBuildings() {
    // TODO: implement
    for (int i = 0; i < buildingCount; i++) {
        Building* building = buildings[i];
        if (!building->isDestroyed()) {
            building->applyEffect(context);
        }
    }
}

void EniesLobbyBattle::checkEndCondition() {
    // TODO: implement
    if (context.robinRescued && context.escapeProgress >= 100) {
        battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN";
    }
    else if (context.busterCallTimer <= 0) {
        battleEnded = true;
        context.resultCode = "BUSTER_CALL";
    }
    else if (isAllStrawHatDead()) {
        battleEnded = true;
        context.resultCode = "CP9_WIN";
    }  
    else if (isAllCP9AgentDead()) {
        battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN_BY_DEFEAT_CP9";
    }
    else if (context.turnCount >= maxTurns) {
        battleEnded = true;
        context.resultCode = "TIME_OUT";
    }
}

bool EniesLobbyBattle::isAllStrawHatDead() {
    for (int i = 0; i < strawHatCount; i++) {
        if (strawHats[i]->isAlive()) {return false;}
    }
    return true;
}
bool EniesLobbyBattle::isAllCP9AgentDead() {
    for (int i = 0; i < cp9Count; i++) {
        if (cp9Agents[i]->isAlive()) {return false;}
    }
    return true;
}

string EniesLobbyBattle::getResult() const {
    // TODO: implement
    return context.resultCode;
}

Character* EniesLobbyBattle::firstStrawHatAlive() const {
    int i = 0;
    while(!strawHats[i]->isAlive() && i < strawHatCount) {
        i++;
    }
    if (i >= strawHatCount) {return nullptr;}
    return strawHats[i];
}

Character* EniesLobbyBattle::firstCP9AgentAlive() const {
    int i = 0;
    while (cp9Agents[i]->isAlive() && i < cp9Count) {
        i++;
    }
    if (i >= cp9Count) {return nullptr;}
    return cp9Agents[i];
}

Character* EniesLobbyBattle::lowestHPCharacterInStrawHat() const {
    Character* resultCharacter = nullptr;
    int minHp = firstStrawHatAlive()->getHP();

    for (int i = 0; i < strawHatCount; i++) {
        Character* current = strawHats[i];
        if (current->isAlive() && current->getHP() < minHp) {
            minHp = current->getHP();
            resultCharacter = current;
        }
    }

    return resultCharacter;
}

Building* EniesLobbyBattle::findBuildingWithName(string name) {
    for (int i = 0; i < buildingCount; i++) {
        Building* current = buildings[i];
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

int setByCondition(int n, int min, int max) {
    if (n < min) {
        return min;
    }
    else if (n > max) {
        return max;
    }
    return n;
}

void EniesLobbyBattle::tempLog() {
    context.logContext();
}

void EniesLobbyBattle::tempLogObjects() {
    cout << "Logging objects" << endl;
    for (int i = 0; i < strawHatCount; i++) {
        cout << strawHats[i]->str() << endl;
    }
    for (int i = 0; i < cp9Count; i++) {
        cout << cp9Agents[i]->str() << endl;
    }
    for (int i = 0; i < buildingCount; i++) {
        cout << buildings[i]->str() << endl;
    }
    cout << "Logging objects completed" << endl;
}

void EniesLobbyBattle::tempLogTurnNode() {
    cout << "Logging turn order" << endl;
    TurnNode* temp = turnOrder;
    while (temp != nullptr) {
        cout << temp->data->str() << endl;
        temp = temp->next;
    }
    cout << "Logging turn order completed" << endl;
}
