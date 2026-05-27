#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "eniesLobby.h"
#include <fstream>
#include <sstream>

#include <sstream>

string str(BattleContext &context) {
  stringstream ss;

  ss << "resultCode=" << context.resultCode << " "
     << "turnCount=" << context.turnCount << " "
     << "morale=" << context.morale << " "
     << "alarmLevel=" << context.alarmLevel << " "
     << "rescueProgress=" << context.rescueProgress << " "
     << "escapeProgress=" << context.escapeProgress << " "
     << "busterCallTimer=" << context.busterCallTimer;

  return ss.str();
}
void printBeforeAfter(Character *actor, Character *target, string action,
                      BattleContext &context) {
  cout << "- " << actor->getName() << " " << action << " -> "
       << target->getName() << endl;
  cout << "actor(before):  " << actor->str()
       << " | alive=" << (actor->isAlive() ? "true" : "false") << endl;
  cout << "target(before): " << target->str()
       << " | alive=" << (target->isAlive() ? "true" : "false") << endl;
  int damage = 0;
  if (action == "special") {
    damage = actor->specialSkill(target, context);
  } else {
    damage = actor->attack(target, context);
  }
  cout << "damage: " << damage << endl;
  cout << "actor(after):   " << actor->str()
       << " | alive=" << (actor->isAlive() ? "true" : "false") << endl;
  cout << "target(after):  " << target->str()
       << " | alive=" << (target->isAlive() ? "true" : "false") << endl;
}
TEST_CASE("test_203")
{
    // 1. Luffy -> MainGate
    // 2. Lucci -> Luffy
    // 3. Luffy -> BusterCallShip
    // 4. Lucci -> Luffy

    Character *luffy = new Luffy("Luffy", 120, 1000, 20, 25, 40, 1500000000LL);
    Building *building = new TowerOfJustice("TowerOfJustice", 35);
    BattleContext context;
    context.rescueProgress = 50;

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=50 escapeProgress=0 busterCallTimer=0");

    context.mainGateDestroyed = true;
    context.robinRescued = true;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=50 escapeProgress=0 busterCallTimer=0");

    context.robinRescued = false;
    context.rescueProgress = 100;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=100 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == true);

    context.mainGateDestroyed = true;
    context.robinRescued = false;
    context.rescueProgress = 50;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=55 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == false);

    for (size_t i = 0; i < 20; i++)
    {
        building->applyEffect(context);
    }
    CHECK(str(context) == "resultCode= turnCount=0 morale=20 alarmLevel=0 rescueProgress=100 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == true);

    delete luffy;
    delete building;
}
TEST_CASE("test_123")
{
    Character *test = new Franky("test", 100, 101, 11, 9, 0, 0);
    Building *building = new MainGate("MainGate", 200);
    BattleContext context;
    CHECK(test->attack(building, context) == 105);
    test->endTurn(context);
    CHECK(test->attack(building, context) == 106);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=101, def=21, speed=9, energy=0, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=200, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_113")
{
    Character *test = new Zoro("test", 100, 100, 6, 0, 20, 0);
    Building *building = new MainGate("MainGate", 120);
    BattleContext context;
    CHECK(test->attack(building, context) == 102);
    test->endTurn(context);
    CHECK(test->attack(building, context) == 102);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=100, def=6, speed=0, energy=20, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=120, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_114")
{
    Character *test = new Zoro("test", 100, 100, 0, 0, 40, 0);
    Building *building = new MainGate("MainGate", 250);
    BattleContext context;
    CHECK(test->specialSkill(building, context) == 220);
    test->endTurn(context);
    CHECK(test->specialSkill(building, context) == 220);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=100, def=0, speed=0, energy=10, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=250, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_118")
{
    Character *test = new Nami("test", 100, 201, 0, 9, 20, 0);
    Building *building = new MainGate("MainGate", 120);
    BattleContext context;
    CHECK(test->attack(building, context) == 101);
    test->endTurn(context);
    CHECK(test->attack(building, context) == 101);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=201, def=0, speed=9, energy=20, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=120, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_120")
{
    BattleContext ctx;
    Character *zoro = new Zoro("Zoro", 100, 100, 51, 0, 20, 0);
    Character *kabu = new Kaku("Kaku", 100, 0, 0, 0, 0, 0);
    CHECK(zoro->specialSkill(kabu, ctx) == 220);
    delete zoro;
    delete kabu;
}
TEST_CASE("test_121")
{
    Character *test = new Usopp("test", 100, 101, 0, 9, 0, 0);
    Building *building = new MainGate("MainGate", 100);
    BattleContext context;
    CHECK(test->attack(building, context) == 51);
    test->endTurn(context);
    CHECK(test->attack(building, context) == 51);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=101, def=0, speed=9, energy=0, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=100, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=25 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_124")
{
    Character *test = new Franky("test", 100, 101, 11, 9, 50, 0);
    Building *building = new MainGate("MainGate", 5000);
    Building *building2 = new MainGate("MainGate", 180);
    BattleContext context;
    CHECK(test->specialSkill(building, context) == 5000);
    test->endTurn(context);
    CHECK(test->specialSkill(building2, context) == 182);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=101, def=21, speed=9, energy=0, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=5000, destroyed=true]");
    CHECK(building2->str() == "Building[name=MainGate, hp=0, maxHP=180, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=40 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
    delete building2;
}
TEST_CASE("test_142")
{
    BattleContext ctx;

    Sanji sanji("Sanji", 100, 40, 20, 20, 50, 1000);
    Jabra jabra("Jabra", 100, 20, 10, 20, 30, 1000);

    int dmg = sanji.attack(&jabra, ctx);

    CHECK(dmg == 45);
}
TEST_CASE("test_107a")
{
    Character *luffy = new Luffy("Luffy", 120, 1000, 20, 25, 40, 1500000000LL);
    Building *building = new BusterCallShip("BusterCallShip", 35);
    BattleContext context;
    context.busterCallTimer = 5;

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=4");

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=3");

    luffy->attack(building, context);
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=6");

    context.busterCallTimer = 0;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode=BUSTER_CALL turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=0");
    // REMINDER applyEffect will update resultCode and battleEnded

    delete luffy;
    delete building;
}
TEST_CASE("test_105")
{
    Character *luffy = new Luffy("Luffy", 120, 1000, 20, 25, 40, 1500000000LL);
    Building *building = new TowerOfJustice("TowerOfJustice", 35);
    BattleContext context;
    context.rescueProgress = 50;

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=50 escapeProgress=0 busterCallTimer=0");

    context.mainGateDestroyed = true;
    context.robinRescued = true;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=50 escapeProgress=0 busterCallTimer=0");

    context.robinRescued = false;
    context.rescueProgress = 100;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=100 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == true);

    context.mainGateDestroyed = true;
    context.robinRescued = false;
    context.rescueProgress = 50;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=55 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == false);

    for (size_t i = 0; i < 20; i++)
    {
        building->applyEffect(context);
    }
    CHECK(str(context) == "resultCode= turnCount=0 morale=20 alarmLevel=0 rescueProgress=100 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == true);

    delete luffy;
    delete building;
}
TEST_CASE("test_201a")
{
    // 1. Luffy -> MainGate
    // 2. Lucci -> Luffy
    ofstream fout("test.txt");
    fout << "CONTEXT 0 0 95 90 99 20\n";
    fout << "STRAW_HAT Luffy 100 100 0 0 0 0\n";
    fout << "CP9 Lucci 100 10 0 0 0 0\n";
    fout << "BUILDING MainGate 100\n";
    fout << "BUILDING Courthouse 100\n";
    fout << "BUILDING TowerOfJustice 100\n";
    fout << "BUILDING BridgeOfHesitation 100\n";
    fout << "BUILDING BusterCallShip 100\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 2 15 10 100 100 97");
    remove("test.txt");
}
TEST_CASE("test_201b")
{
    ofstream fout("test.txt");
    fout << "CONTEXT 0 0 95 90 99 20\n";
    fout << "STRAW_HAT Luffy 100 100 0 0 0 0\n";
    fout << "CP9 Lucci 100 10 0 0 0 0\n";
    fout << "BUILDING MainGate 100\n";
    fout << "BUILDING Courthouse 100\n";
    fout << "BUILDING TowerOfJustice 100\n";
    fout << "BUILDING BridgeOfHesitation 100\n";
    fout << "BUILDING BusterCallShip 100\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 2 15 10 100 100 97");
    remove("test.txt");
}
TEST_CASE("test_201f")
{
    ofstream fout("test.txt");
    fout << "CONTEXT 0 0 93 90 99 20\n";
    fout << "STRAW_HAT Luffy 100 10 0 0 0 0\n";
    fout << "CP9 Lucci 100 20 0 0 0 0\n";
    fout << "BUILDING MainGate 300\n";
    fout << "BUILDING Courthouse 300\n";
    fout << "BUILDING TowerOfJustice 169\n";
    fout << "BUILDING BridgeOfHesitation 100\n";
    fout << "BUILDING BusterCallShip 100\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 10 3 50 93 90 89");
    remove("test.txt");
}
TEST_CASE("test_007")
{
    Character *strawHats[3];
    strawHats[0] = new Luffy("Luffy", 120, 35, 20, 25, 50, 1500000000LL);
    strawHats[1] = new Nami("Nami", 80, 22, 12, 35, 60, 366000000LL);
    strawHats[2] = new Franky("Franky", 130, 32, 28, 18, 50, 394000000LL);

    Character *cp9[3];
    cp9[0] = new Lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    cp9[1] = new Kaku("Kaku", 130, 35, 22, 28, 55, 2200);
    cp9[2] = new Kalifa("Kalifa", 95, 26, 18, 32, 50, 630);

    BattleContext context;

    ostringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());
    cout << "\n[Round 1] StrawHat attacks" << endl;
    printBeforeAfter(strawHats[0], cp9[0], "special", context);
    printBeforeAfter(strawHats[1], cp9[1], "attack", context);
    printBeforeAfter(strawHats[2], cp9[2], "special", context);

    cout << "\n[Round 2] CP9 attacks" << endl;
    printBeforeAfter(cp9[0], strawHats[0], "attack", context);
    printBeforeAfter(cp9[1], strawHats[1], "special", context);
    printBeforeAfter(cp9[2], strawHats[2], "special", context);
    cout.rdbuf(old);
    CHECK(buffer.str() == "\n"
                          "[Round 1] StrawHat attacks\n"
                          "- Luffy special -> Lucci\n"
                          "actor(before):  StrawHat[name=Luffy, hp=120, atk=35, def=20, speed=25, energy=50, bounty=1500000000] | alive=true\n"
                          "target(before): CP9[name=Lucci, hp=150, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "damage: 45\n"
                          "actor(after):   StrawHat[name=Luffy, hp=110, atk=50, def=20, speed=40, energy=30, bounty=1500000000] | alive=true\n"
                          "target(after):  CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "- Nami attack -> Kaku\n"
                          "actor(before):  StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "target(before): CP9[name=Kaku, hp=130, atk=35, def=22, speed=28, energy=55, doriki=2200] | alive=true\n"
                          "damage: 6\n"
                          "actor(after):   StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "target(after):  CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, energy=55, doriki=2200] | alive=true\n"
                          "- Franky special -> Kalifa\n"
                          "actor(before):  StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=50, bounty=394000000] | alive=true\n"
                          "target(before): CP9[name=Kalifa, hp=95, atk=26, def=18, speed=32, energy=50, doriki=630] | alive=true\n"
                          "damage: 21\n"
                          "actor(after):   StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=20, bounty=394000000] | alive=true\n"
                          "target(after):  CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, energy=50, doriki=630] | alive=true\n"
                          "\n"
                          "[Round 2] CP9 attacks\n"
                          "- Lucci attack -> Luffy\n"
                          "actor(before):  CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "target(before): StrawHat[name=Luffy, hp=110, atk=50, def=20, speed=40, energy=30, bounty=1500000000] | alive=true\n"
                          "damage: 220\n"
                          "actor(after):   CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "target(after):  StrawHat[name=Luffy, hp=0, atk=50, def=20, speed=40, energy=30, bounty=1500000000] | alive=false\n"
                          "- Kaku special -> Nami\n"
                          "actor(before):  CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, energy=55, doriki=2200] | alive=true\n"
                          "target(before): StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "damage: 69\n"
                          "actor(after):   CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, energy=35, doriki=2200] | alive=true\n"
                          "target(after):  StrawHat[name=Nami, hp=11, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "- Kalifa special -> Franky\n"
                          "actor(before):  CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, energy=50, doriki=630] | alive=true\n"
                          "target(before): StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=20, bounty=394000000] | alive=true\n"
                          "damage: 9\n"
                          "actor(after):   CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, energy=32, doriki=630] | alive=true\n"
                          "target(after):  StrawHat[name=Franky, hp=121, atk=32, def=28, speed=12, energy=20, bounty=394000000] | alive=true\n");
    for (int i = 0; i < 3; i++)
        delete strawHats[i];
    for (int i = 0; i < 3; i++)
        delete cp9[i];
}
TEST_CASE("test_036")
{
    BattleContext ctx;
    Character *sanji = new Sanji("Sanji", 101, 103, 2, 51, 18, 0);
    Character *kabu = new Kaku("Jabra", 200, 0, 20, 0, 0, 0);
    CHECK(sanji->specialSkill(kabu, ctx) == 197);
    sanji->endTurn(ctx);
    CHECK(sanji->str() == "StrawHat[name=Sanji, hp=101, atk=103, def=2, speed=51, energy=0, bounty=0]");
    CHECK(kabu->str() == "CP9[name=Jabra, hp=3, atk=0, def=12, speed=0, energy=0, doriki=0]");
    CHECK(str(ctx) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=0");

    delete sanji;
    delete kabu;
}
TEST_CASE("test_201c")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 181\n";
    fout << "BUILDING BusterCallShip 242\n";
    fout << "CP9 Kalifa 110 25 29 31 37 4738\n";
    fout << "STRAW_HAT Usopp 100 46 20 40 30 469927601\n";
    fout << "STRAW_HAT Sanji 156 92 25 27 78 402486553\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 152 46 10 13 66 2515\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "STRAW_HAT Luffy 168 97 8 14 56 631532060\n";
    fout << "STRAW_HAT Zoro 196 57 32 40 45 254535967\n";
    fout << "STRAW_HAT Chopper 193 92 17 45 35 822650416\n";
    fout << "STRAW_HAT Franky 100 86 39 31 47 599149657\n";
    fout << "STRAW_HAT Nami 69 46 25 16 71 632226456\n";
    fout << "CP9 Lucci 114 45 13 12 62 2605\n";
    fout << "BUILDING MainGate 241\n";
    fout << "CP9 Blueno 129 54 22 16 63 3594\n";
    fout << "CP9 Jabra 103 36 23 32 78 3590\n";
    fout << "CP9 Fukurou 153 42 28 41 70 3114\n";
    fout << "CP9 Kumadori 135 39 34 12 39 3415\n";
    fout << "CONTEXT 41 61 49 10 46 50\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 49 53 71 100 53 0");
    remove("test.txt");
}
TEST_CASE("test_202")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 200\n";
    fout << "BUILDING BusterCallShip 245\n";
    fout << "CP9 Kalifa 100 30 29 31 37 4738\n";
    fout << "STRAW_HAT Usopp 100 46 20 40 30 469927601\n";
    fout << "STRAW_HAT Sanji 156 92 25 27 78 402486553\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 140 45 15 13 66 2515\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "STRAW_HAT Luffy 168 10 8 14 56 631532060\n";
    fout << "STRAW_HAT Zoro 196 57 32 40 45 254535967\n";
    fout << "STRAW_HAT Chopper 193 92 17 45 35 822650416\n";
    fout << "STRAW_HAT Franky 100 86 39 31 47 599149657\n";
    fout << "STRAW_HAT Nami 69 46 25 16 71 632226456\n";
    fout << "CP9 Lucci 114 45 13 12 62 2605\n";
    fout << "BUILDING MainGate 241\n";
    fout << "CP9 Blueno 129 54 22 16 63 3594\n";
    fout << "CP9 Jabra 105 36 23 32 78 3590\n";
    fout << "CP9 Fukurou 153 42 28 41 70 3114\n";
    fout << "CP9 Kumadori 135 39 34 12 39 3415\n";
    fout << "CONTEXT 41 61 49 10 46 50\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 49 38 71 100 58 0");
    remove("test.txt");
}
TEST_CASE("test_203")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 210\n";
    fout << "BUILDING BusterCallShip 245\n";
    fout << "CP9 Kalifa 89 30 29 31 37 4738\n";
    fout << "STRAW_HAT Usopp 90 46 20 40 30 469927601\n";
    fout << "STRAW_HAT Sanji 156 92 25 27 78 402486553\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 140 45 15 13 66 2515\n";
    fout << "BUILDING TowerOfJustice 253\n";
    fout << "STRAW_HAT Luffy 168 10 8 14 56 631532060\n";
    fout << "STRAW_HAT Zoro 196 57 42 40 45 254535967\n";
    fout << "STRAW_HAT Chopper 193 22 17 45 35 822650416\n";
    fout << "STRAW_HAT Franky 100 100 39 31 47 599149657\n";
    fout << "STRAW_HAT Nami 69 46 25 16 71 632226456\n";
    fout << "CP9 Lucci 115 45 13 12 62 2605\n";
    fout << "BUILDING MainGate 241\n";
    fout << "CP9 Blueno 130 54 22 16 63 3594\n";
    fout << "CP9 Jabra 110 36 23 32 78 3590\n";
    fout << "CP9 Fukurou 150 42 28 41 70 3114\n";
    fout << "CP9 Kumadori 140 39 35 12 39 3415\n";
    fout << "CONTEXT 41 61 49 10 46 50\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 40 37 61 100 58 9");
    remove("test.txt");
}
TEST_CASE("test_custom")
{
    ofstream fout("test.txt");
    fout << "STRAW_HAT Sanji 61 87 31 26 52 687662824\n";
    fout << "STRAW_HAT Zoro 177 54 30 29 65 77823766\n";
    fout << "BUILDING BusterCallShip 110\n";
    fout << "BUILDING BridgeOfHesitation 237\n";
    fout << "CP9 Jabra 130 34 31 46 72 3445\n";
    fout << "CP9 Kalifa 93 33 32 43 78 2906\n";
    fout << "STRAW_HAT Luffy 182 71 12 31 78 639711058\n";
    fout << "CONTEXT 67 80 33 6 114 68\n";
    fout << "CP9 Kaku 109 27 30 21 69 2552\n";
    fout << "BUILDING MainGate 237\n";
    fout << "STRAW_HAT Chopper 194 79 16 16 75 873746660\n";
    fout << "STRAW_HAT Franky 75 46 27 44 57 91303998\n";
    fout << "STRAW_HAT Nami 68 16 40 43 32 551697738\n";
    fout << "BUILDING TowerOfJustice 202\n";
    fout << "CP9 Fukurou 83 50 27 21 41 2745\n";
    fout << "CP9 Lucci 159 38 15 44 70 4227\n";
    fout << "CP9 Kumadori 110 53 15 52 77 2735\n";
    fout << "STRAW_HAT Usopp 153 72 35 43 45 682319368\n";
    fout << "CP9 Blueno 107 29 15 46 35 2932\n";
    fout << "BUILDING Courthouse 229\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 54 64 85 100 57 61");
    remove("test.txt");
}
TEST_CASE("test_custom_2")
{
    ofstream fout("test.txt");
    fout << "BUILDING TowerOfJustice 234\n";
    fout << "CP9 Kumadori 155 52 14 38 52 2391\n";
    fout << "CP9 Fukurou 109 40 17 20 71 3764\n";
    fout << "CP9 Kalifa 80 52 16 43 39 4306\n";
    fout << "CP9 Blueno 83 32 18 47 46 2713\n";
    fout << "STRAW_HAT Franky 82 68 12 12 59 919986281\n";
    fout << "CONTEXT 64 24 27 18 95 98\n";
    fout << "BUILDING Courthouse 167\n";
    fout << "STRAW_HAT Luffy 185 62 26 23 70 448507398\n";
    fout << "BUILDING MainGate 116\n";
    fout << "BUILDING BridgeOfHesitation 199\n";
    fout << "STRAW_HAT Sanji 64 45 40 45 51 848339955\n";
    fout << "STRAW_HAT Nami 161 46 7 58 50 879539162\n";
    fout << "STRAW_HAT Usopp 157 38 16 32 36 907192188\n";
    fout << "CP9 Jabra 148 31 30 58 58 4136\n";
    fout << "CP9 Lucci 147 41 17 49 70 2392\n";
    fout << "STRAW_HAT Chopper 146 81 33 58 47 298185501\n";
    fout << "STRAW_HAT Zoro 193 58 9 13 74 469718161\n";
    fout << "BUILDING BusterCallShip 232\n";
    fout << "CP9 Kaku 119 21 29 41 79 2641\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 90 100 75 100 69 7");
    remove("test.txt");
}
TEST_CASE("test_custom_3")
{
    ofstream fout("test.txt");
    fout << "STRAW_HAT Sanji 61 87 31 26 52 687662824\n";
    fout << "STRAW_HAT Zoro 177 54 30 29 65 77823766\n";
    fout << "BUILDING BusterCallShip 110\n";
    fout << "BUILDING BridgeOfHesitation 237\n";
    fout << "CP9 Jabra 130 34 31 46 72 3445\n";
    fout << "CP9 Kalifa 93 33 32 43 78 2906\n";
    fout << "STRAW_HAT Luffy 182 71 12 31 78 639711058\n";
    fout << "CONTEXT 67 80 33 6 114 68\n";
    fout << "CP9 Kaku 109 27 30 21 69 2552\n";
    fout << "BUILDING MainGate 237\n";
    fout << "STRAW_HAT Chopper 194 79 16 16 75 873746660\n";
    fout << "STRAW_HAT Franky 75 46 27 44 57 91303998\n";
    fout << "STRAW_HAT Nami 68 16 40 43 32 551697738\n";
    fout << "BUILDING TowerOfJustice 202\n";
    fout << "CP9 Fukurou 83 50 27 21 41 2745\n";
    fout << "CP9 Lucci 159 38 15 44 70 4227\n";
    fout << "CP9 Kumadori 110 53 15 52 77 2735\n";
    fout << "STRAW_HAT Usopp 153 72 35 43 45 682319368\n";
    fout << "CP9 Blueno 107 29 15 46 35 2932\n";
    fout << "BUILDING Courthouse 229\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 54 64 85 100 57 61");
    remove("test.txt");
}
TEST_CASE("test_custom_4")
{
    ofstream fout("test.txt");
    fout << "STRAW_HAT Franky 122 50 33 28 31 626242953\n";
    fout << "BUILDING MainGate 222\n";
    fout << "BUILDING BridgeOfHesitation 132\n";
    fout << "CONTEXT 81 21 20 18 106 34\n";
    fout << "CP9 Kaku 144 39 11 44 40 2764\n";
    fout << "STRAW_HAT Luffy 178 20 15 27 41 800611678\n";
    fout << "BUILDING Courthouse 142\n";
    fout << "STRAW_HAT Sanji 170 22 37 32 51 753776330\n";
    fout << "CP9 Blueno 89 34 13 31 70 2731\n";
    fout << "STRAW_HAT Nami 126 81 34 60 52 582640542\n";
    fout << "CP9 Kalifa 121 43 22 29 42 3565\n";
    fout << "CP9 Lucci 103 39 11 36 41 2481\n";
    fout << "STRAW_HAT Zoro 133 24 12 10 41 877977010\n";
    fout << "STRAW_HAT Chopper 113 69 15 28 57 332699724\n";
    fout << "CP9 Kumadori 160 26 27 50 63 2288\n";
    fout << "CP9 Jabra 148 45 24 17 38 3043\n";
    fout << "BUILDING TowerOfJustice 115\n";
    fout << "CP9 Fukurou 143 23 25 31 59 3172\n";
    fout << "STRAW_HAT Usopp 77 81 34 40 77 889925265\n";
    fout << "BUILDING BusterCallShip 175\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 26 84 75 100 100 82");
    remove("test.txt");
}
TEST_CASE("test_custom_5")
{
    ofstream fout("test.txt");
    fout << "BUILDING TowerOfJustice 234\n";
    fout << "CP9 Kumadori 155 52 14 38 52 2391\n";
    fout << "CP9 Fukurou 109 40 17 20 71 3764\n";
    fout << "CP9 Kalifa 80 52 16 43 39 4306\n";
    fout << "CP9 Blueno 83 32 18 47 46 2713\n";
    fout << "STRAW_HAT Franky 82 68 12 12 59 919986281\n";
    fout << "CONTEXT 64 24 27 18 95 98\n";
    fout << "BUILDING Courthouse 167\n";
    fout << "STRAW_HAT Luffy 185 62 26 23 70 448507398\n";
    fout << "BUILDING MainGate 116\n";
    fout << "BUILDING BridgeOfHesitation 199\n";
    fout << "STRAW_HAT Sanji 64 45 40 45 51 848339955\n";
    fout << "STRAW_HAT Nami 161 46 7 58 50 879539162\n";
    fout << "STRAW_HAT Usopp 157 38 16 32 36 907192188\n";
    fout << "CP9 Jabra 148 31 30 58 58 4136\n";
    fout << "CP9 Lucci 147 41 17 49 70 2392\n";
    fout << "STRAW_HAT Chopper 146 81 33 58 47 298185501\n";
    fout << "STRAW_HAT Zoro 193 58 9 13 74 469718161\n";
    fout << "BUILDING BusterCallShip 232\n";
    fout << "CP9 Kaku 119 21 29 41 79 2641\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 90 100 75 100 69 7");
    remove("test.txt");
}
TEST_CASE("test_custom_6")
{
    ofstream fout("test.txt");
    fout << "BUILDING BridgeOfHesitation 240\n";
    fout << "STRAW_HAT Usopp 199 74 33 15 36 427533703\n";
    fout << "CP9 Kalifa 147 30 14 34 80 3235\n";
    fout << "BUILDING TowerOfJustice 227\n";
    fout << "BUILDING MainGate 112\n";
    fout << "STRAW_HAT Sanji 144 42 31 18 72 668322512\n";
    fout << "STRAW_HAT Zoro 180 100 37 37 31 88928134\n";
    fout << "STRAW_HAT Nami 80 46 34 59 37 675421570\n";
    fout << "CP9 Kaku 156 24 25 48 44 2995\n";
    fout << "CP9 Lucci 91 47 31 37 61 3019\n";
    fout << "STRAW_HAT Franky 126 95 39 45 67 643174077\n";
    fout << "CP9 Kumadori 151 49 23 49 45 2593\n";
    fout << "CP9 Jabra 152 42 33 27 57 2782\n";
    fout << "CP9 Fukurou 140 32 18 23 36 2657\n";
    fout << "BUILDING Courthouse 247\n";
    fout << "STRAW_HAT Luffy 188 61 39 29 43 735735461\n";
    fout << "BUILDING BusterCallShip 136\n";
    fout << "CP9 Blueno 127 44 29 57 41 4955\n";
    fout << "CONTEXT 69 80 50 27 72 79\n";
    fout << "STRAW_HAT Chopper 186 31 16 53 49 806919028\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 73 79 100 100 80 0");
    remove("test.txt");
}
TEST_CASE("test_custom_7")
{
    ofstream fout("test.txt");
    fout << "CP9 Lucci 151 30 12 42 57 2867\n";
    fout << "BUILDING BridgeOfHesitation 113\n";
    fout << "STRAW_HAT Franky 85 89 31 36 65 359952722\n";
    fout << "STRAW_HAT Nami 130 73 31 55 59 142554415\n";
    fout << "STRAW_HAT Sanji 71 63 27 28 65 76116512\n";
    fout << "STRAW_HAT Luffy 77 60 39 25 51 736877312\n";
    fout << "BUILDING TowerOfJustice 228\n";
    fout << "BUILDING BusterCallShip 219\n";
    fout << "STRAW_HAT Usopp 133 90 37 30 69 73260165\n";
    fout << "BUILDING MainGate 175\n";
    fout << "CP9 Jabra 99 49 18 11 68 3648\n";
    fout << "CONTEXT 87 80 21 50 19 82\n";
    fout << "CP9 Kumadori 97 52 27 51 54 3219\n";
    fout << "CP9 Kalifa 98 36 13 40 37 3846\n";
    fout << "BUILDING Courthouse 125\n";
    fout << "STRAW_HAT Chopper 192 60 26 29 56 584565802\n";
    fout << "CP9 Kaku 126 24 12 56 78 3142\n";
    fout << "CP9 Fukurou 97 23 32 60 62 4986\n";
    fout << "CP9 Blueno 157 53 14 45 59 4143\n";
    fout << "STRAW_HAT Zoro 155 85 10 11 54 69067358\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 46 100 75 100 99 8");
    remove("test.txt");
}
TEST_CASE("test_custom_8")
{
    ofstream fout("test.txt");
    fout << "CP9 Blueno 152 23 30 60 73 2828\n";
    fout << "CP9 Kumadori 135 24 34 27 39 2689\n";
    fout << "BUILDING TowerOfJustice 217\n";
    fout << "STRAW_HAT Luffy 182 39 31 22 30 78756167\n";
    fout << "CONTEXT 59 61 34 23 98 81\n";
    fout << "BUILDING BusterCallShip 158\n";
    fout << "CP9 Kaku 102 53 24 45 46 2775\n";
    fout << "STRAW_HAT Nami 86 30 18 41 52 503771739\n";
    fout << "CP9 Kalifa 160 38 13 54 77 2017\n";
    fout << "STRAW_HAT Usopp 123 80 5 39 80 560640737\n";
    fout << "CP9 Fukurou 138 32 30 16 68 2036\n";
    fout << "CP9 Jabra 121 26 29 11 64 4043\n";
    fout << "STRAW_HAT Franky 179 44 7 35 72 452491176\n";
    fout << "STRAW_HAT Sanji 148 90 32 50 57 86199666\n";
    fout << "STRAW_HAT Zoro 63 87 22 45 33 698384531\n";
    fout << "STRAW_HAT Chopper 177 18 30 43 75 637799594\n";
    fout << "BUILDING MainGate 145\n";
    fout << "BUILDING BridgeOfHesitation 155\n";
    fout << "CP9 Lucci 135 48 34 38 40 3880\n";
    fout << "BUILDING Courthouse 201\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 48 100 56 100 77 52");
    remove("test.txt");
}
TEST_CASE("test_142")
{
    BattleContext ctx;

    Sanji sanji("Sanji", 100, 40, 20, 20, 50, 1000);
    Jabra jabra("Jabra", 100, 20, 10, 20, 30, 1000);

    int dmg = sanji.attack(&jabra, ctx);

    CHECK(dmg == 45);
}
TEST_CASE("test_107b")
{
    Character *luffy = new Luffy("Luffy", 120, 1000, 20, 25, 40, 1500000000LL);
    Building *building = new BusterCallShip("BusterCallShip", 35);
    BattleContext context;
    context.busterCallTimer = 5;

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=4");

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=3");

    luffy->attack(building, context);
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=6");

    context.busterCallTimer = 0;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode=BUSTER_CALL turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=0");
    // REMINDER: Same as test_107a

    delete luffy;
    delete building;
}
TEST_CASE("test_105")
{
    Character *luffy = new Luffy("Luffy", 120, 1000, 20, 25, 40, 1500000000LL);
    Building *building = new TowerOfJustice("TowerOfJustice", 35);
    BattleContext context;
    context.rescueProgress = 50;

    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=50 escapeProgress=0 busterCallTimer=0");

    context.mainGateDestroyed = true;
    context.robinRescued = true;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=50 escapeProgress=0 busterCallTimer=0");

    context.robinRescued = false;
    context.rescueProgress = 100;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=100 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == true);

    context.mainGateDestroyed = true;
    context.robinRescued = false;
    context.rescueProgress = 50;
    building->applyEffect(context);
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=55 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == false);

    for (size_t i = 0; i < 20; i++)
    {
        building->applyEffect(context);
    }
    CHECK(str(context) == "resultCode= turnCount=0 morale=20 alarmLevel=0 rescueProgress=100 escapeProgress=0 busterCallTimer=0");
    CHECK(context.robinRescued == true);

    delete luffy;
    delete building;
}
TEST_CASE("test_custom_9")
{
    ofstream fout("test.txt");
    fout << "STRAW_HAT Nami 196 21 39 45 53 677452973\n";
    fout << "CP9 Kaku 137 44 12 60 80 4208\n";
    fout << "CP9 Kalifa 104 39 30 33 53 3417\n";
    fout << "BUILDING BusterCallShip 242\n";
    fout << "CP9 Jabra 80 26 16 42 49 4919\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "CP9 Fukurou 88 42 17 53 30 4667\n";
    fout << "CONTEXT 74 35 35 49 86 61\n";
    fout << "BUILDING BridgeOfHesitation 231\n";
    fout << "STRAW_HAT Franky 167 77 18 30 50 81125479\n";
    fout << "STRAW_HAT Luffy 60 95 32 44 34 447394900\n";
    fout << "CP9 Blueno 140 44 18 15 51 4600\n";
    fout << "CP9 Kumadori 122 35 17 26 42 4220\n";
    fout << "BUILDING Courthouse 149\n";
    fout << "BUILDING MainGate 236\n";
    fout << "STRAW_HAT Zoro 194 32 18 41 76 551880258\n";
    fout << "STRAW_HAT Usopp 85 97 18 42 63 219846164\n";
    fout << "STRAW_HAT Chopper 154 68 13 25 49 32504509\n";
    fout << "STRAW_HAT Sanji 148 59 5 20 62 263701367\n";
    fout << "CP9 Lucci 143 41 21 47 34 3588\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 19 100 40 100 100 68");
    remove("test.txt");
}
TEST_CASE("test_custom_10")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 181\n";
    fout << "BUILDING BusterCallShip 242\n";
    fout << "CP9 Kalifa 110 25 29 31 37 4738\n";
    fout << "STRAW_HAT Usopp 100 46 20 40 30 469927601\n";
    fout << "STRAW_HAT Sanji 156 92 25 27 78 402486553\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 152 46 10 13 66 2515\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "STRAW_HAT Luffy 168 97 8 14 56 631532060\n";
    fout << "STRAW_HAT Zoro 196 57 32 40 45 254535967\n";
    fout << "STRAW_HAT Chopper 193 92 17 45 35 822650416\n";
    fout << "STRAW_HAT Franky 100 86 39 31 47 599149657\n";
    fout << "STRAW_HAT Nami 69 46 25 16 71 632226456\n";
    fout << "CP9 Lucci 114 45 13 12 62 2605\n";
    fout << "BUILDING MainGate 241\n";
    fout << "CP9 Blueno 129 54 22 16 63 3594\n";
    fout << "CP9 Jabra 103 36 23 32 78 3590\n";
    fout << "CP9 Fukurou 153 42 28 41 70 3114\n";
    fout << "CP9 Kumadori 135 39 34 12 39 3415\n";
    fout << "CONTEXT 41 61 49 10 46 50\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 49 53 71 100 53 0");
    remove("test.txt");
}
TEST_CASE("test_201d")
{
    // 1. Luffy -> MainGate
    // 2. Lucci -> Luffy
    ofstream fout("test.txt");
    fout << "CONTEXT 0 0 95 90 99 20\n";
    fout << "STRAW_HAT Luffy 100 100 0 0 0 0\n";
    fout << "CP9 Lucci 100 10 0 0 0 0\n";
    fout << "BUILDING MainGate 100\n";
    fout << "BUILDING Courthouse 100\n";
    fout << "BUILDING TowerOfJustice 100\n";
    fout << "BUILDING BridgeOfHesitation 100\n";
    fout << "BUILDING BusterCallShip 100\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 2 15 10 100 100 97");
    remove("test.txt");
}
TEST_CASE("test_007")
{
    Character *strawHats[3];
    strawHats[0] = new Luffy("Luffy", 120, 35, 20, 25, 50, 1500000000LL);
    strawHats[1] = new Nami("Nami", 80, 22, 12, 35, 60, 366000000LL);
    strawHats[2] = new Franky("Franky", 130, 32, 28, 18, 50, 394000000LL);

    Character *cp9[3];
    cp9[0] = new Lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    cp9[1] = new Kaku("Kaku", 130, 35, 22, 28, 55, 2200);
    cp9[2] = new Kalifa("Kalifa", 95, 26, 18, 32, 50, 630);

    BattleContext context;

    ostringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());
    cout << "\n[Round 1] StrawHat attacks" << endl;
    printBeforeAfter(strawHats[0], cp9[0], "special", context);
    printBeforeAfter(strawHats[1], cp9[1], "attack", context);
    printBeforeAfter(strawHats[2], cp9[2], "special", context);

    cout << "\n[Round 2] CP9 attacks" << endl;
    printBeforeAfter(cp9[0], strawHats[0], "attack", context);
    printBeforeAfter(cp9[1], strawHats[1], "special", context);
    printBeforeAfter(cp9[2], strawHats[2], "special", context);
    cout.rdbuf(old);
    CHECK(buffer.str() == "\n"
                          "[Round 1] StrawHat attacks\n"
                          "- Luffy special -> Lucci\n"
                          "actor(before):  StrawHat[name=Luffy, hp=120, atk=35, def=20, speed=25, energy=50, bounty=1500000000] | alive=true\n"
                          "target(before): CP9[name=Lucci, hp=150, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "damage: 45\n"
                          "actor(after):   StrawHat[name=Luffy, hp=110, atk=50, def=20, speed=40, energy=30, bounty=1500000000] | alive=true\n"
                          "target(after):  CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "- Nami attack -> Kaku\n"
                          "actor(before):  StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "target(before): CP9[name=Kaku, hp=130, atk=35, def=22, speed=28, energy=55, doriki=2200] | alive=true\n"
                          "damage: 6\n"
                          "actor(after):   StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "target(after):  CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, energy=55, doriki=2200] | alive=true\n"
                          "- Franky special -> Kalifa\n"
                          "actor(before):  StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=50, bounty=394000000] | alive=true\n"
                          "target(before): CP9[name=Kalifa, hp=95, atk=26, def=18, speed=32, energy=50, doriki=630] | alive=true\n"
                          "damage: 21\n"
                          "actor(after):   StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=20, bounty=394000000] | alive=true\n"
                          "target(after):  CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, energy=50, doriki=630] | alive=true\n"
                          "\n"
                          "[Round 2] CP9 attacks\n"
                          "- Lucci attack -> Luffy\n"
                          "actor(before):  CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "target(before): StrawHat[name=Luffy, hp=110, atk=50, def=20, speed=40, energy=30, bounty=1500000000] | alive=true\n"
                          "damage: 220\n"
                          "actor(after):   CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, energy=60, doriki=4000] | alive=true\n"
                          "target(after):  StrawHat[name=Luffy, hp=0, atk=50, def=20, speed=40, energy=30, bounty=1500000000] | alive=false\n"
                          "- Kaku special -> Nami\n"
                          "actor(before):  CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, energy=55, doriki=2200] | alive=true\n"
                          "target(before): StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "damage: 69\n"
                          "actor(after):   CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, energy=35, doriki=2200] | alive=true\n"
                          "target(after):  StrawHat[name=Nami, hp=11, atk=22, def=12, speed=35, energy=60, bounty=366000000] | alive=true\n"
                          "- Kalifa special -> Franky\n"
                          "actor(before):  CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, energy=50, doriki=630] | alive=true\n"
                          "target(before): StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=20, bounty=394000000] | alive=true\n"
                          "damage: 9\n"
                          "actor(after):   CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, energy=32, doriki=630] | alive=true\n"
                          "target(after):  StrawHat[name=Franky, hp=121, atk=32, def=28, speed=12, energy=20, bounty=394000000] | alive=true\n");
    for (int i = 0; i < 3; i++)
        delete strawHats[i];
    for (int i = 0; i < 3; i++)
        delete cp9[i];
}
TEST_CASE("test_custom_11")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 181\n";
    fout << "BUILDING BusterCallShip 242\n";
    fout << "CP9 Kalifa 110 25 29 31 37 4738\n";
    fout << "STRAW_HAT Usopp 100 46 20 40 30 469927601\n";
    fout << "STRAW_HAT Sanji 156 92 25 27 78 402486553\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 152 46 10 13 66 2515\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "STRAW_HAT Luffy 168 97 8 14 56 631532060\n";
    fout << "STRAW_HAT Zoro 196 57 32 40 45 254535967\n";
    fout << "STRAW_HAT Chopper 193 92 17 45 35 822650416\n";
    fout << "STRAW_HAT Franky 100 86 39 31 47 599149657\n";
    fout << "STRAW_HAT Nami 69 46 25 16 71 632226456\n";
    fout << "CP9 Lucci 114 45 13 12 62 2605\n";
    fout << "BUILDING MainGate 241\n";
    fout << "CP9 Blueno 129 54 22 16 63 3594\n";
    fout << "CP9 Jabra 103 36 23 32 78 3590\n";
    fout << "CP9 Fukurou 153 42 28 41 70 3114\n";
    fout << "CP9 Kumadori 135 39 34 12 39 3415\n";
    fout << "CONTEXT 41 61 49 10 46 50\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 49 53 71 100 53 0");
    remove("test.txt");
}
TEST_CASE("test_201e")
{
    // 1. Luffy -> MainGate
    // 2. Lucci -> Luffy
    ofstream fout("test.txt");
    fout << "CONTEXT 0 0 95 90 99 20\n";
    fout << "STRAW_HAT Luffy 100 100 0 0 0 0\n";
    fout << "CP9 Lucci 100 10 0 0 0 0\n";
    fout << "BUILDING MainGate 100\n";
    fout << "BUILDING Courthouse 100\n";
    fout << "BUILDING TowerOfJustice 100\n";
    fout << "BUILDING BridgeOfHesitation 100\n";
    fout << "BUILDING BusterCallShip 100\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 2 15 10 100 100 97");
    remove("test.txt");
}
TEST_CASE("test_208")
{
    // 1. Luffy -> MainGate
    // 2. Chopper -> Luffy
    // 3. Lucci -> Luffy
    // 4. Luffy -> MainGate
    // 5. Chopper -> Luffy
    // 6. Lucci -> Luffy -> Luffy death
    // 8. Chopper -> Chopper
    // 9. Lucci -> Chopper
    // 11. Chopper -> Chopper
    // 12. Lucci -> Chopper

    ofstream fout("test.txt");
    fout << "CONTEXT 0 0 0 0 50 20\n";
    fout << "STRAW_HAT Luffy 100 90 0 0 0 0\n";
    fout << "STRAW_HAT Chopper 100 10 0 0 100 0\n";
    fout << "CP9 Lucci 180 90 0 0 0 0\n";
    fout << "BUILDING MainGate 120\n";
    fout << "BUILDING Courthouse 100\n";
    fout << "BUILDING TowerOfJustice 100\n";
    fout << "BUILDING BridgeOfHesitation 100\n";
    fout << "BUILDING BusterCallShip 100\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 12 18 60 65 0 38");
    remove("test.txt");
}
TEST_CASE("test_142")
{
    BattleContext ctx;

    Sanji sanji("Sanji", 100, 40, 20, 20, 50, 1000);
    Jabra jabra("Jabra", 100, 20, 10, 20, 30, 1000);

    int dmg = sanji.attack(&jabra, ctx);

    CHECK(dmg == 45);
}
TEST_CASE("test_custom_12")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 181\n";
    fout << "BUILDING BusterCallShip 242\n";
    fout << "CP9 Kalifa 110 25 29 31 37 4738\n";
    fout << "STRAW_HAT Usopp 100 46 20 40 30 469927601\n";
    fout << "STRAW_HAT Sanji 156 92 25 27 78 402486553\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 152 46 10 13 66 2515\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "STRAW_HAT Luffy 168 97 8 14 56 631532060\n";
    fout << "STRAW_HAT Zoro 196 57 32 40 45 254535967\n";
    fout << "STRAW_HAT Chopper 193 92 17 45 35 822650416\n";
    fout << "STRAW_HAT Franky 100 86 39 31 47 599149657\n";
    fout << "STRAW_HAT Nami 69 46 25 16 71 632226456\n";
    fout << "CP9 Lucci 114 45 13 12 62 2605\n";
    fout << "BUILDING MainGate 241\n";
    fout << "CP9 Blueno 129 54 22 16 63 3594\n";
    fout << "CP9 Jabra 103 36 23 32 78 3590\n";
    fout << "CP9 Fukurou 153 42 28 41 70 3114\n";
    fout << "CP9 Kumadori 135 39 34 12 39 3415\n";
    fout << "CONTEXT 41 61 49 10 46 50\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 49 53 71 100 53 0");
    remove("test.txt");
}
TEST_CASE("test_131")
{
    BattleContext ctx;
    ctx.busterCallTimer = 1;

    BusterCallShip ship("Buster", 100);

    ship.applyEffect(ctx);

    CHECK(ctx.busterCallTimer == 0);
    CHECK(ctx.battleEnded == true);
    CHECK(ctx.resultCode == "BUSTER_CALL");
}
TEST_CASE("test_124")
{
    Character *test = new Franky("test", 100, 101, 11, 9, 50, 0);
    Building *building = new MainGate("MainGate", 5000);
    Building *building2 = new MainGate("MainGate", 180);
    BattleContext context;
    CHECK(test->specialSkill(building, context) == 5000);
    test->endTurn(context);
    CHECK(test->specialSkill(building2, context) == 182);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=101, def=21, speed=9, energy=0, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=5000, destroyed=true]");
    CHECK(building2->str() == "Building[name=MainGate, hp=0, maxHP=180, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=10 alarmLevel=0 rescueProgress=40 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
    delete building2;
}
TEST_CASE("test_121")
{
    Character *test = new Usopp("test", 100, 101, 0, 9, 0, 0);
    Building *building = new MainGate("MainGate", 100);
    BattleContext context;
    CHECK(test->attack(building, context) == 51);
    test->endTurn(context);
    CHECK(test->attack(building, context) == 51);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=101, def=0, speed=9, energy=0, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=100, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=25 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_120")
{
    BattleContext ctx;
    Character *zoro = new Zoro("Zoro", 100, 100, 51, 0, 20, 0);
    Character *kabu = new Kaku("Kaku", 100, 0, 0, 0, 0, 0);
    CHECK(zoro->specialSkill(kabu, ctx) == 220);
    delete zoro;
    delete kabu;
}
TEST_CASE("test_119")
{
    Character *test = new Nami("test", 100, 101, 0, 9, 40, 0);
    Building *building = new MainGate("MainGate", 400);
    BattleContext context;
    CHECK(test->specialSkill(building, context) == 212);
    test->endTurn(context);
    CHECK(test->specialSkill(building, context) == 212);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=101, def=0, speed=9, energy=0, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=400, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=2");

    delete test;
    delete building;
}
TEST_CASE("test_114")
{
    Character *test = new Zoro("test", 100, 100, 0, 0, 40, 0);
    Building *building = new MainGate("MainGate", 250);
    BattleContext context;
    CHECK(test->specialSkill(building, context) == 220);
    test->endTurn(context);
    CHECK(test->specialSkill(building, context) == 220);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=100, def=0, speed=0, energy=10, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=250, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_custom_random")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 194\n";
    fout << "BUILDING BusterCallShip 218\n";
    fout << "CP9 Kalifa 105 42 18 35 64 384729104\n";
    fout << "STRAW_HAT Usopp 114 63 27 15 48 502419385\n";
    fout << "STRAW_HAT Sanji 132 81 39 42 61 719402563\n";
    fout << "BUILDING BridgeOfHesitation 157\n";
    fout << "CP9 Kaku 128 31 24 53 47 4839\n";
    fout << "BUILDING TowerOfJustice 205\n";
    fout << "STRAW_HAT Luffy 145 55 19 33 72 391054286\n";
    fout << "STRAW_HAT Zoro 163 74 41 22 59 845291307\n";
    fout << "STRAW_HAT Chopper 121 49 35 11 68 194850372\n";
    fout << "STRAW_HAT Franky 172 23 14 58 36 620584719\n";
    fout << "STRAW_HAT Nami 95 88 30 27 52 315482960\n";
    fout << "CP9 Lucci 149 51 22 46 70 5193\n";
    fout << "BUILDING MainGate 183\n";
    fout << "CP9 Blueno 111 37 16 60 43 2748\n";
    fout << "CP9 Jabra 138 29 33 17 55 1952\n";
    fout << "CP9 Fukurou 124 46 25 39 67 4310\n";
    fout << "CP9 Kumadori 102 58 11 44 31 3824\n";
    fout << "CONTEXT 53 72 38 15 89 44\n";

    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    
    CHECK(battle.getResult() == "TIME_OUT 44 68 77 100 58 47");
    
    remove("test.txt");
}
TEST_CASE("test_custom_random_1")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 112\n";
    fout << "BUILDING BusterCallShip 198\n";
    fout << "CP9 Kalifa 145 31 12 55 42 291503847\n";
    fout << "STRAW_HAT Usopp 88 52 41 29 63 601928475\n";
    fout << "STRAW_HAT Sanji 120 73 16 48 35 342910586\n";
    fout << "BUILDING BridgeOfHesitation 215\n";
    fout << "CP9 Kaku 102 59 33 11 74 1845\n";
    fout << "BUILDING TowerOfJustice 167\n";
    fout << "STRAW_HAT Luffy 193 26 24 38 51 825491036\n";
    fout << "STRAW_HAT Zoro 134 85 15 52 69 471029385\n";
    fout << "STRAW_HAT Chopper 156 44 38 17 40 915830247\n";
    fout << "STRAW_HAT Franky 115 91 22 30 57 205847193\n";
    fout << "STRAW_HAT Nami 178 37 49 43 31 539201847\n";
    fout << "CP9 Lucci 127 48 29 25 66 4192\n";
    fout << "BUILDING MainGate 139\n";
    fout << "CP9 Blueno 150 21 17 46 53 3029\n";
    fout << "CP9 Jabra 93 64 35 32 48 2847\n";
    fout << "CP9 Fukurou 139 50 11 14 78 4930\n";
    fout << "CP9 Kumadori 118 33 26 60 52 1956\n";
    fout << "CONTEXT 76 29 55 41 63 87\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 17 71 29 100 100 47");
    remove("test.txt");
}

TEST_CASE("test_custom_random_2")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 245\n";
    fout << "BUILDING BusterCallShip 153\n";
    fout << "CP9 Kalifa 82 61 38 14 59 738492015\n";
    fout << "STRAW_HAT Usopp 164 29 15 53 47 194850273\n";
    fout << "STRAW_HAT Sanji 105 88 43 21 70 820491385\n";
    fout << "BUILDING BridgeOfHesitation 182\n";
    fout << "CP9 Kaku 149 42 27 36 33 3925\n";
    fout << "BUILDING TowerOfJustice 119\n";
    fout << "STRAW_HAT Luffy 123 74 19 49 65 582910473\n";
    fout << "STRAW_HAT Zoro 187 35 31 16 52 295018473\n";
    fout << "STRAW_HAT Chopper 141 53 50 42 38 483920154\n";
    fout << "STRAW_HAT Franky 199 15 11 27 76 710492835\n";
    fout << "STRAW_HAT Nami 136 92 25 58 41 639205814\n";
    fout << "CP9 Lucci 108 57 14 30 55 2184\n";
    fout << "BUILDING MainGate 206\n";
    fout << "CP9 Blueno 124 39 46 22 68 4739\n";
    fout << "CP9 Jabra 155 47 18 60 44 3105\n";
    fout << "CP9 Fukurou 91 23 32 45 61 1958\n";
    fout << "CP9 Kumadori 132 50 20 13 78 2847\n";
    fout << "CONTEXT 43 85 19 64 32 55\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 34 48 80 100 87 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_3")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 168\n";
    fout << "BUILDING BusterCallShip 231\n";
    fout << "CP9 Kalifa 119 54 22 47 31 105938472\n";
    fout << "STRAW_HAT Usopp 142 77 36 12 55 930482516\n";
    fout << "STRAW_HAT Sanji 185 39 18 59 43 472910583\n";
    fout << "BUILDING BridgeOfHesitation 140\n";
    fout << "CP9 Kaku 113 25 45 31 67 2948\n";
    fout << "BUILDING TowerOfJustice 251\n";
    fout << "STRAW_HAT Luffy 81 94 13 26 79 384920516\n";
    fout << "STRAW_HAT Zoro 158 63 49 41 36 620584913\n";
    fout << "STRAW_HAT Chopper 197 19 27 53 50 184930275\n";
    fout << "STRAW_HAT Franky 126 82 11 16 62 502914837\n";
    fout << "STRAW_HAT Nami 104 46 34 38 74 719402853\n";
    fout << "CP9 Lucci 141 33 50 20 58 3752\n";
    fout << "BUILDING MainGate 177\n";
    fout << "CP9 Blueno 96 58 16 43 40 4829\n";
    fout << "CP9 Jabra 135 41 29 55 69 1930\n";
    fout << "CP9 Fukurou 152 28 14 18 52 3847\n";
    fout << "CP9 Kumadori 107 49 38 60 45 2749\n";
    fout << "CONTEXT 92 41 68 25 74 39\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 39 77 51 100 88 38");
    remove("test.txt");
}

TEST_CASE("test_custom_random_4")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 209\n";
    fout << "BUILDING BusterCallShip 124\n";
    fout << "CP9 Kalifa 136 22 43 19 70 592014837\n";
    fout << "STRAW_HAT Usopp 105 85 16 44 38 384920157\n";
    fout << "STRAW_HAT Sanji 162 49 31 52 59 719482053\n";
    fout << "BUILDING BridgeOfHesitation 193\n";
    fout << "CP9 Kaku 157 37 14 60 51 4029\n";
    fout << "BUILDING TowerOfJustice 142\n";
    fout << "STRAW_HAT Luffy 114 93 49 28 42 294850173\n";
    fout << "STRAW_HAT Zoro 179 61 25 13 77 602948153\n";
    fout << "STRAW_HAT Chopper 138 34 50 36 65 849302154\n";
    fout << "STRAW_HAT Franky 83 76 11 57 33 104928475\n";
    fout << "STRAW_HAT Nami 191 18 28 41 54 930582147\n";
    fout << "CP9 Lucci 125 55 37 23 48 3194\n";
    fout << "BUILDING MainGate 248\n";
    fout << "CP9 Blueno 144 43 20 47 63 2740\n";
    fout << "CP9 Jabra 101 50 33 15 79 4920\n";
    fout << "CP9 Fukurou 119 27 18 53 45 1843\n";
    fout << "CP9 Kumadori 150 31 46 32 56 3759\n";
    fout << "CONTEXT 55 63 32 84 47 91\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 57 73 100 100 34");
    remove("test.txt");
}

TEST_CASE("test_custom_random_5")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 144\n";
    fout << "BUILDING BusterCallShip 237\n";
    fout << "CP9 Kalifa 94 58 26 33 45 401928473\n";
    fout << "STRAW_HAT Usopp 173 41 42 56 31 829501473\n";
    fout << "STRAW_HAT Sanji 111 96 15 18 73 602948371\n";
    fout << "BUILDING BridgeOfHesitation 116\n";
    fout << "CP9 Kaku 134 29 48 44 60 1958\n";
    fout << "BUILDING TowerOfJustice 211\n";
    fout << "STRAW_HAT Luffy 156 64 30 12 55 384029157\n";
    fout << "STRAW_HAT Zoro 99 78 19 39 67 104928374\n";
    fout << "STRAW_HAT Chopper 182 23 34 51 42 719483025\n";
    fout << "STRAW_HAT Franky 147 50 50 27 79 930481572\n";
    fout << "STRAW_HAT Nami 128 85 11 60 48 502941837\n";
    fout << "CP9 Lucci 159 36 22 15 54 4829\n";
    fout << "BUILDING MainGate 189\n";
    fout << "CP9 Blueno 106 47 37 49 38 3104\n";
    fout << "CP9 Jabra 142 53 14 22 66 2749\n";
    fout << "CP9 Fukurou 122 19 29 57 71 3840\n";
    fout << "CP9 Kumadori 175 42 41 30 50 1937\n";
    fout << "CONTEXT 34 77 91 46 58 62\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 48 92 75 100 69 13");
    remove("test.txt");
}

TEST_CASE("test_custom_random_6")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 225\n";
    fout << "BUILDING BusterCallShip 163\n";
    fout << "CP9 Kalifa 152 44 19 60 53 930481275\n";
    fout << "STRAW_HAT Usopp 121 73 34 25 77 472910485\n";
    fout << "STRAW_HAT Sanji 194 36 46 41 39 104928375\n";
    fout << "BUILDING BridgeOfHesitation 249\n";
    fout << "CP9 Kaku 116 51 11 16 68 3847\n";
    fout << "BUILDING TowerOfJustice 134\n";
    fout << "STRAW_HAT Luffy 140 88 28 54 46 602941837\n";
    fout << "STRAW_HAT Zoro 171 19 40 32 62 829501472\n";
    fout << "STRAW_HAT Chopper 103 62 15 47 31 384029154\n";
    fout << "STRAW_HAT Franky 158 55 50 13 74 719483026\n";
    fout << "STRAW_HAT Nami 86 95 23 37 50 502948173\n";
    fout << "CP9 Lucci 133 30 33 58 42 2749\n";
    fout << "BUILDING MainGate 157\n";
    fout << "CP9 Blueno 177 47 14 21 65 4103\n";
    fout << "CP9 Jabra 125 58 27 49 57 1958\n";
    fout << "CP9 Fukurou 149 24 42 33 35 3194\n";
    fout << "CP9 Kumadori 92 41 49 11 79 4830\n";
    fout << "CONTEXT 61 52 44 79 36 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 13 68 62 100 100 24");
    remove("test.txt");
}

TEST_CASE("test_custom_random_7")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 187\n";
    fout << "BUILDING BusterCallShip 104\n";
    fout << "CP9 Kalifa 113 27 50 36 66 294850173\n";
    fout << "STRAW_HAT Usopp 149 91 16 57 41 719402853\n";
    fout << "STRAW_HAT Sanji 82 59 33 14 78 502914837\n";
    fout << "BUILDING BridgeOfHesitation 173\n";
    fout << "CP9 Kaku 155 46 22 43 49 4829\n";
    fout << "BUILDING TowerOfJustice 218\n";
    fout << "STRAW_HAT Luffy 176 34 45 19 55 930482516\n";
    fout << "STRAW_HAT Zoro 127 76 11 52 32 384920516\n";
    fout << "STRAW_HAT Chopper 191 50 29 26 73 184930275\n";
    fout << "STRAW_HAT Franky 138 43 38 60 60 620584913\n";
    fout << "STRAW_HAT Nami 109 82 14 31 44 472910583\n";
    fout << "CP9 Lucci 122 64 41 12 57 1930\n";
    fout << "BUILDING MainGate 233\n";
    fout << "CP9 Blueno 141 38 18 47 36 3752\n";
    fout << "CP9 Jabra 164 21 46 25 71 2749\n";
    fout << "CP9 Fukurou 98 55 34 33 53 3847\n";
    fout << "CP9 Kumadori 134 49 15 58 79 4829\n";
    fout << "CONTEXT 49 81 54 28 67 43\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 42 24 70 100 91 27");
    remove("test.txt");
}

TEST_CASE("test_custom_random_8")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 136\n";
    fout << "BUILDING BusterCallShip 252\n";
    fout << "CP9 Kalifa 164 43 14 49 52 639205814\n";
    fout << "STRAW_HAT Usopp 108 76 46 27 76 295018473\n";
    fout << "STRAW_HAT Sanji 153 29 25 58 41 710492835\n";
    fout << "BUILDING BridgeOfHesitation 122\n";
    fout << "CP9 Kaku 129 57 38 16 65 2184\n";
    fout << "BUILDING TowerOfJustice 194\n";
    fout << "STRAW_HAT Luffy 187 88 19 60 33 820491385\n";
    fout << "STRAW_HAT Zoro 94 61 32 13 78 738492015\n";
    fout << "STRAW_HAT Chopper 145 35 11 36 59 194850273\n";
    fout << "STRAW_HAT Franky 121 92 31 53 44 483920154\n";
    fout << "STRAW_HAT Nami 173 50 50 42 70 582910473\n";
    fout << "CP9 Lucci 114 23 15 45 47 3105\n";
    fout << "BUILDING MainGate 169\n";
    fout << "CP9 Blueno 149 53 41 22 68 4739\n";
    fout << "CP9 Jabra 82 15 27 30 61 1958\n";
    fout << "CP9 Fukurou 138 39 33 55 55 3925\n";
    fout << "CP9 Kumadori 157 47 18 21 38 2847\n";
    fout << "CONTEXT 83 36 71 52 44 60\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 47 86 36 100 70 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_9")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 211\n";
    fout << "BUILDING BusterCallShip 179\n";
    fout << "CP9 Kalifa 127 50 35 14 74 539201847\n";
    fout << "STRAW_HAT Usopp 193 91 17 48 31 205847193\n";
    fout << "STRAW_HAT Sanji 156 33 49 46 66 915830247\n";
    fout << "BUILDING BridgeOfHesitation 147\n";
    fout << "CP9 Kaku 106 64 22 43 53 3029\n";
    fout << "BUILDING TowerOfJustice 239\n";
    fout << "STRAW_HAT Luffy 118 47 26 11 57 342910586\n";
    fout << "STRAW_HAT Zoro 178 26 12 60 78 825491036\n";
    fout << "STRAW_HAT Chopper 142 58 16 32 42 291503847\n";
    fout << "STRAW_HAT Franky 88 44 11 25 63 601928475\n";
    fout << "STRAW_HAT Nami 139 73 38 17 40 471029385\n";
    fout << "CP9 Lucci 150 29 41 15 48 2847\n";
    fout << "BUILDING MainGate 122\n";
    fout << "CP9 Blueno 121 21 29 55 52 4192\n";
    fout << "CP9 Jabra 175 37 33 52 69 4930\n";
    fout << "CP9 Fukurou 94 85 15 30 35 1845\n";
    fout << "CP9 Kumadori 134 53 14 38 45 1956\n";
    fout << "CONTEXT 62 48 76 33 94 51\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 51 73 63 100 61 45");
    remove("test.txt");
}

TEST_CASE("test_custom_random_10")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 158\n";
    fout << "BUILDING BusterCallShip 224\n";
    fout << "CP9 Kalifa 144 34 46 32 56 620584719\n";
    fout << "STRAW_HAT Usopp 119 76 11 57 33 315482960\n";
    fout << "STRAW_HAT Sanji 150 18 28 41 54 845291307\n";
    fout << "BUILDING BridgeOfHesitation 183\n";
    fout << "CP9 Kaku 101 55 37 23 48 2748\n";
    fout << "BUILDING TowerOfJustice 248\n";
    fout << "STRAW_HAT Luffy 138 43 20 47 63 719402563\n";
    fout << "STRAW_HAT Zoro 83 50 33 15 79 502419385\n";
    fout << "STRAW_HAT Chopper 191 27 18 53 45 384729104\n";
    fout << "STRAW_HAT Franky 125 31 46 17 55 194850372\n";
    fout << "STRAW_HAT Nami 111 61 25 13 77 519300000\n";
    fout << "CP9 Lucci 136 49 31 52 59 1952\n";
    fout << "BUILDING MainGate 142\n";
    fout << "CP9 Blueno 105 85 16 44 38 4310\n";
    fout << "CP9 Jabra 162 22 43 19 70 3824\n";
    fout << "CP9 Fukurou 157 37 14 60 51 2740\n";
    fout << "CP9 Kumadori 114 93 49 28 42 3594\n";
    fout << "CONTEXT 51 44 83 62 38 74\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 9 63 54 100 100 30");
    remove("test.txt");
}
TEST_CASE("test_custom_random_11")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 221\n";
    fout << "BUILDING BusterCallShip 143\n";
    fout << "CP9 Kalifa 115 53 24 39 67 295810473\n";
    fout << "STRAW_HAT Usopp 179 42 18 60 44 639205814\n";
    fout << "STRAW_HAT Sanji 138 23 32 45 61 194850273\n";
    fout << "BUILDING BridgeOfHesitation 194\n";
    fout << "CP9 Kaku 108 50 20 13 78 4739\n";
    fout << "BUILDING TowerOfJustice 125\n";
    fout << "STRAW_HAT Luffy 132 57 14 30 55 582910473\n";
    fout << "STRAW_HAT Zoro 155 39 46 22 68 295018473\n";
    fout << "STRAW_HAT Chopper 124 47 18 60 44 820491385\n";
    fout << "STRAW_HAT Franky 91 61 38 14 59 710492835\n";
    fout << "STRAW_HAT Nami 149 29 15 53 47 483920154\n";
    fout << "CP9 Lucci 164 88 43 21 70 3105\n";
    fout << "BUILDING MainGate 206\n";
    fout << "CP9 Blueno 157 35 31 16 52 1958\n";
    fout << "CP9 Jabra 119 53 50 42 38 2847\n";
    fout << "CP9 Fukurou 123 15 11 27 76 3925\n";
    fout << "CP9 Kumadori 187 92 25 58 41 2184\n";
    fout << "CONTEXT 52 19 64 32 55 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 56 44 34 100 90 1");
    remove("test.txt");
}

TEST_CASE("test_custom_random_12")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 176\n";
    fout << "BUILDING BusterCallShip 238\n";
    fout << "CP9 Kalifa 141 58 16 43 40 719402853\n";
    fout << "STRAW_HAT Usopp 135 41 29 55 69 502914837\n";
    fout << "STRAW_HAT Sanji 152 28 14 18 52 930482516\n";
    fout << "BUILDING BridgeOfHesitation 113\n";
    fout << "CP9 Kaku 107 49 38 60 45 1930\n";
    fout << "BUILDING TowerOfJustice 219\n";
    fout << "STRAW_HAT Luffy 119 54 22 47 31 384920516\n";
    fout << "STRAW_HAT Zoro 142 77 36 12 55 184930275\n";
    fout << "STRAW_HAT Chopper 185 39 18 59 43 620584913\n";
    fout << "STRAW_HAT Franky 81 94 13 26 79 472910583\n";
    fout << "STRAW_HAT Nami 158 63 49 41 36 105938472\n";
    fout << "CP9 Lucci 197 19 27 53 50 3752\n";
    fout << "BUILDING MainGate 140\n";
    fout << "CP9 Blueno 126 82 11 16 62 4829\n";
    fout << "CP9 Jabra 104 46 34 38 74 2749\n";
    fout << "CP9 Fukurou 133 33 50 20 58 3847\n";
    fout << "CP9 Kumadori 96 58 16 43 40 4829\n";
    fout << "CONTEXT 41 68 25 74 39 92\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 17 38 75 100 100 23");
    remove("test.txt");
}

TEST_CASE("test_custom_random_13")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 144\n";
    fout << "BUILDING BusterCallShip 191\n";
    fout << "CP9 Kalifa 125 55 37 23 48 294850173\n";
    fout << "STRAW_HAT Usopp 144 43 20 47 63 602948153\n";
    fout << "STRAW_HAT Sanji 101 50 33 15 79 849302154\n";
    fout << "BUILDING BridgeOfHesitation 248\n";
    fout << "CP9 Kaku 119 27 18 53 45 104928475\n";
    fout << "BUILDING TowerOfJustice 157\n";
    fout << "STRAW_HAT Luffy 136 22 43 19 70 930582147\n";
    fout << "STRAW_HAT Zoro 105 85 16 44 38 384920157\n";
    fout << "STRAW_HAT Chopper 162 49 31 52 59 719482053\n";
    fout << "STRAW_HAT Franky 157 37 14 60 51 3194\n";
    fout << "STRAW_HAT Nami 114 93 49 28 42 2740\n";
    fout << "CP9 Lucci 179 61 25 13 77 4920\n";
    fout << "BUILDING MainGate 193\n";
    fout << "CP9 Blueno 138 34 50 36 65 1843\n";
    fout << "CP9 Jabra 83 76 11 57 33 3759\n";
    fout << "CP9 Fukurou 150 31 46 32 56 4029\n";
    fout << "CP9 Kumadori 209 18 28 41 54 2090\n";
    fout << "CONTEXT 63 32 84 47 91 55\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 13 65 42 100 100 79");
    remove("test.txt");
}

TEST_CASE("test_custom_random_14")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 189\n";
    fout << "BUILDING BusterCallShip 106\n";
    fout << "CP9 Kalifa 159 36 22 15 54 401928473\n";
    fout << "STRAW_HAT Usopp 106 47 37 49 38 829501473\n";
    fout << "STRAW_HAT Sanji 142 53 14 22 66 602948371\n";
    fout << "BUILDING BridgeOfHesitation 122\n";
    fout << "CP9 Kaku 122 19 29 57 71 1958\n";
    fout << "BUILDING TowerOfJustice 175\n";
    fout << "STRAW_HAT Luffy 94 58 26 33 45 384029157\n";
    fout << "STRAW_HAT Zoro 173 41 42 56 31 104928374\n";
    fout << "STRAW_HAT Chopper 111 96 15 18 73 719483025\n";
    fout << "STRAW_HAT Franky 134 29 48 44 60 930481572\n";
    fout << "STRAW_HAT Nami 156 64 30 12 55 502941837\n";
    fout << "CP9 Lucci 99 78 19 39 67 4829\n";
    fout << "BUILDING MainGate 116\n";
    fout << "CP9 Blueno 182 23 34 51 42 3104\n";
    fout << "CP9 Jabra 147 50 50 27 79 2749\n";
    fout << "CP9 Fukurou 128 85 11 60 48 3840\n";
    fout << "CP9 Kumadori 144 42 41 30 50 1937\n";
    fout << "CONTEXT 77 91 46 58 62 34\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 15 78 75 100 100 48");
    remove("test.txt");
}

TEST_CASE("test_custom_random_15")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 157\n";
    fout << "BUILDING BusterCallShip 177\n";
    fout << "CP9 Kalifa 133 30 33 58 42 930481275\n";
    fout << "STRAW_HAT Usopp 116 51 11 16 68 472910485\n";
    fout << "STRAW_HAT Sanji 125 58 27 49 57 104928375\n";
    fout << "BUILDING BridgeOfHesitation 149\n";
    fout << "CP9 Kaku 92 41 49 11 79 3847\n";
    fout << "BUILDING TowerOfJustice 249\n";
    fout << "STRAW_HAT Luffy 152 44 19 60 53 602941837\n";
    fout << "STRAW_HAT Zoro 121 73 34 25 77 829501472\n";
    fout << "STRAW_HAT Chopper 194 36 46 41 39 384029154\n";
    fout << "STRAW_HAT Franky 140 88 28 54 46 719483026\n";
    fout << "STRAW_HAT Nami 171 19 40 32 62 502948173\n";
    fout << "CP9 Lucci 103 62 15 47 31 2749\n";
    fout << "BUILDING MainGate 134\n";
    fout << "CP9 Blueno 158 55 50 13 74 4103\n";
    fout << "CP9 Jabra 86 95 23 37 50 1958\n";
    fout << "CP9 Fukurou 149 24 42 33 35 3194\n";
    fout << "CP9 Kumadori 225 47 14 21 65 4830\n";
    fout << "CONTEXT 52 44 79 36 83 61\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 38 31 34 100 59 48");
    remove("test.txt");
}

TEST_CASE("test_custom_random_16")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 233\n";
    fout << "BUILDING BusterCallShip 141\n";
    fout << "CP9 Kalifa 122 64 41 12 57 294850173\n";
    fout << "STRAW_HAT Usopp 155 46 22 43 49 719402853\n";
    fout << "STRAW_HAT Sanji 164 21 46 25 71 502914837\n";
    fout << "BUILDING BridgeOfHesitation 113\n";
    fout << "CP9 Kaku 98 55 34 33 53 4829\n";
    fout << "BUILDING TowerOfJustice 173\n";
    fout << "STRAW_HAT Luffy 113 27 50 36 66 930482516\n";
    fout << "STRAW_HAT Zoro 149 91 16 57 41 384920516\n";
    fout << "STRAW_HAT Chopper 82 59 33 14 78 184930275\n";
    fout << "STRAW_HAT Franky 176 34 45 19 55 620584913\n";
    fout << "STRAW_HAT Nami 127 76 11 52 32 472910583\n";
    fout << "CP9 Lucci 191 50 29 26 73 1930\n";
    fout << "BUILDING MainGate 218\n";
    fout << "CP9 Blueno 138 43 38 60 60 3752\n";
    fout << "CP9 Jabra 109 82 14 31 44 2749\n";
    fout << "CP9 Fukurou 134 49 15 58 79 3847\n";
    fout << "CP9 Kumadori 187 38 18 47 36 4829\n";
    fout << "CONTEXT 81 54 28 67 43 49\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 38 68 64 100 90 6");
    remove("test.txt");
}

TEST_CASE("test_custom_random_17")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 169\n";
    fout << "BUILDING BusterCallShip 149\n";
    fout << "CP9 Kalifa 114 23 15 45 47 639205814\n";
    fout << "STRAW_HAT Usopp 129 57 38 16 65 295018473\n";
    fout << "STRAW_HAT Sanji 82 15 27 30 61 710492835\n";
    fout << "BUILDING BridgeOfHesitation 129\n";
    fout << "CP9 Kaku 138 39 33 55 55 2184\n";
    fout << "BUILDING TowerOfJustice 122\n";
    fout << "STRAW_HAT Luffy 164 43 14 49 52 820491385\n";
    fout << "STRAW_HAT Zoro 108 76 46 27 76 738492015\n";
    fout << "STRAW_HAT Chopper 153 29 25 58 41 194850273\n";
    fout << "STRAW_HAT Franky 187 88 19 60 33 483920154\n";
    fout << "STRAW_HAT Nami 94 61 32 13 78 582910473\n";
    fout << "CP9 Lucci 145 35 11 36 59 3105\n";
    fout << "BUILDING MainGate 194\n";
    fout << "CP9 Blueno 121 92 31 53 44 4739\n";
    fout << "CP9 Jabra 173 50 50 42 70 1958\n";
    fout << "CP9 Fukurou 157 47 18 21 38 3925\n";
    fout << "CP9 Kumadori 136 53 41 22 68 2847\n";
    fout << "CONTEXT 36 71 52 44 60 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 42 27 65 100 92 21");
    remove("test.txt");
}

TEST_CASE("test_custom_random_18")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 122\n";
    fout << "BUILDING BusterCallShip 121\n";
    fout << "CP9 Kalifa 150 29 41 15 48 539201847\n";
    fout << "STRAW_HAT Usopp 106 64 22 43 53 205847193\n";
    fout << "STRAW_HAT Sanji 175 37 33 52 69 915830247\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 94 85 15 30 35 3029\n";
    fout << "BUILDING TowerOfJustice 147\n";
    fout << "STRAW_HAT Luffy 127 50 35 14 74 342910586\n";
    fout << "STRAW_HAT Zoro 193 91 17 48 31 825491036\n";
    fout << "STRAW_HAT Chopper 156 33 49 46 66 291503847\n";
    fout << "STRAW_HAT Franky 118 47 26 11 57 601928475\n";
    fout << "STRAW_HAT Nami 178 26 12 60 78 471029385\n";
    fout << "CP9 Lucci 142 58 16 32 42 2847\n";
    fout << "BUILDING MainGate 239\n";
    fout << "CP9 Blueno 88 44 11 25 63 4192\n";
    fout << "CP9 Jabra 139 73 38 17 40 4930\n";
    fout << "CP9 Fukurou 134 53 14 38 45 1845\n";
    fout << "CP9 Kumadori 211 17 29 55 52 1956\n";
    fout << "CONTEXT 48 76 33 94 51 62\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 1 58 81 33 100 50");
    remove("test.txt");
}

TEST_CASE("test_custom_random_19")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 142\n";
    fout << "BUILDING BusterCallShip 105\n";
    fout << "CP9 Kalifa 136 49 31 52 59 620584719\n";
    fout << "STRAW_HAT Usopp 157 37 14 60 51 315482960\n";
    fout << "STRAW_HAT Sanji 114 93 49 28 42 845291307\n";
    fout << "BUILDING BridgeOfHesitation 157\n";
    fout << "CP9 Kaku 105 85 16 44 38 2748\n";
    fout << "BUILDING TowerOfJustice 111\n";
    fout << "STRAW_HAT Luffy 144 34 46 32 56 719402563\n";
    fout << "STRAW_HAT Zoro 119 76 11 57 33 502419385\n";
    fout << "STRAW_HAT Chopper 150 18 28 41 54 384729104\n";
    fout << "STRAW_HAT Franky 125 31 46 17 55 194850372\n";
    fout << "STRAW_HAT Nami 162 22 43 19 70 519300000\n";
    fout << "CP9 Lucci 111 61 25 13 77 1952\n";
    fout << "BUILDING MainGate 114\n";
    fout << "CP9 Blueno 138 43 20 47 63 4310\n";
    fout << "CP9 Jabra 83 50 33 15 79 3824\n";
    fout << "CP9 Fukurou 191 27 18 53 45 2740\n";
    fout << "CP9 Kumadori 158 55 37 23 48 3594\n";
    fout << "CONTEXT 44 83 62 38 74 51\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 42 26 65 100 46 35");
    remove("test.txt");
}

TEST_CASE("test_custom_random_20")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 118\n";
    fout << "BUILDING BusterCallShip 178\n";
    fout << "CP9 Kalifa 142 58 16 32 42 104928475\n";
    fout << "STRAW_HAT Usopp 88 44 11 25 63 930582147\n";
    fout << "STRAW_HAT Sanji 139 73 38 17 40 384920157\n";
    fout << "BUILDING BridgeOfHesitation 239\n";
    fout << "CP9 Kaku 134 53 14 38 45 3194\n";
    fout << "BUILDING TowerOfJustice 121\n";
    fout << "STRAW_HAT Luffy 127 50 35 14 74 294850173\n";
    fout << "STRAW_HAT Zoro 193 91 17 48 31 602948153\n";
    fout << "STRAW_HAT Chopper 156 33 49 46 66 849302154\n";
    fout << "STRAW_HAT Franky 150 29 41 15 48 4920\n";
    fout << "STRAW_HAT Nami 121 21 29 55 52 2740\n";
    fout << "CP9 Lucci 175 37 33 52 69 1843\n";
    fout << "BUILDING MainGate 106\n";
    fout << "CP9 Blueno 94 85 15 30 35 3759\n";
    fout << "CP9 Jabra 211 17 29 55 52 4029\n";
    fout << "CP9 Fukurou 106 64 22 43 53 2090\n";
    fout << "CP9 Kumadori 211 26 12 60 78 3594\n";
    fout << "CONTEXT 76 33 94 51 62 48\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 42 61 28 100 74 22");
    remove("test.txt");
}
TEST_CASE("test_005") {
  Character *strawHats[7];
  strawHats[0] = new Luffy("Luffy", 120, 35, 20, 25, 50, 1500000000LL);
  strawHats[1] = new Zoro("Zoro", 110, 38, 25, 20, 45, 1111000000LL);
  strawHats[2] = new Sanji("Sanji", 100, 34, 18, 30, 45, 1032000000LL);
  strawHats[3] = new Nami("Nami", 80, 22, 12, 35, 60, 366000000LL);
  strawHats[4] = new Chopper("Chopper", 90, 20, 15, 22, 55, 1000LL);
  strawHats[5] = new Usopp("Usopp", 85, 24, 14, 28, 50, 500000000LL);
  strawHats[6] = new Franky("Franky", 130, 32, 28, 18, 50, 394000000LL);

  ostringstream buffer;
  streambuf *old = cout.rdbuf(buffer.rdbuf());
  for (int i = 0; i < 7; i++) {
    cout << "- " << strawHats[i]->str()
         << " | isStrawHat=" << (strawHats[i]->isStrawHat() ? "true" : "false")
         << " | isCP9=" << (strawHats[i]->isCP9() ? "true" : "false") << endl;
  }
  cout.rdbuf(old);
  CHECK(buffer.str() ==
        "- StrawHat[name=Luffy, hp=120, atk=35, def=20, speed=25, energy=50, "
        "bounty=1500000000] | isStrawHat=true | isCP9=false\n"
        "- StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, energy=45, "
        "bounty=1111000000] | isStrawHat=true | isCP9=false\n"
        "- StrawHat[name=Sanji, hp=100, atk=34, def=18, speed=30, energy=45, "
        "bounty=1032000000] | isStrawHat=true | isCP9=false\n"
        "- StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, energy=60, "
        "bounty=366000000] | isStrawHat=true | isCP9=false\n"
        "- StrawHat[name=Chopper, hp=90, atk=20, def=15, speed=22, energy=55, "
        "bounty=1000] | isStrawHat=true | isCP9=false\n"
        "- StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, energy=50, "
        "bounty=500000000] | isStrawHat=true | isCP9=false\n"
        "- StrawHat[name=Franky, hp=130, atk=32, def=28, speed=18, energy=50, "
        "bounty=394000000] | isStrawHat=true | isCP9=false\n");
  for (int i = 0; i < 7; i++)
    delete strawHats[i];
}

TEST_CASE("test_006") {
  Character *cp9[7];
  cp9[0] = new Lucci("Lucci", 150, 40, 25, 30, 60, 4000);
  cp9[1] = new Kaku("Kaku", 130, 35, 22, 28, 55, 2200);
  cp9[2] = new Jabra("Jabra", 125, 33, 30, 24, 50, 2180);
  cp9[3] = new Blueno("Blueno", 110, 28, 24, 26, 45, 820);
  cp9[4] = new Kalifa("Kalifa", 95, 26, 18, 32, 50, 630);
  cp9[5] = new Kumadori("Kumadori", 115, 30, 20, 20, 45, 810);
  cp9[6] = new Fukurou("Fukurou", 100, 27, 16, 25, 40, 800);

  ostringstream buffer;
  streambuf *old = cout.rdbuf(buffer.rdbuf());
  for (int i = 0; i < 7; i++) {
    cout << "- " << cp9[i]->str()
         << " | isStrawHat=" << (cp9[i]->isStrawHat() ? "true" : "false")
         << " | isCP9=" << (cp9[i]->isCP9() ? "true" : "false") << endl;
  }
  cout.rdbuf(old);
  CHECK(buffer.str() ==
        "- CP9[name=Lucci, hp=150, atk=40, def=25, speed=30, energy=60, "
        "doriki=4000] | isStrawHat=false | isCP9=true\n"
        "- CP9[name=Kaku, hp=130, atk=35, def=22, speed=28, energy=55, "
        "doriki=2200] | isStrawHat=false | isCP9=true\n"
        "- CP9[name=Jabra, hp=125, atk=33, def=30, speed=24, energy=50, "
        "doriki=2180] | isStrawHat=false | isCP9=true\n"
        "- CP9[name=Blueno, hp=110, atk=28, def=24, speed=26, energy=45, "
        "doriki=820] | isStrawHat=false | isCP9=true\n"
        "- CP9[name=Kalifa, hp=95, atk=26, def=18, speed=32, energy=50, "
        "doriki=630] | isStrawHat=false | isCP9=true\n"
        "- CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, energy=45, "
        "doriki=810] | isStrawHat=false | isCP9=true\n"
        "- CP9[name=Fukurou, hp=100, atk=27, def=16, speed=25, energy=40, "
        "doriki=800] | isStrawHat=false | isCP9=true\n");
  for (int i = 0; i < 7; i++)
    delete cp9[i];
}

TEST_CASE("test_007") {
  Character *strawHats[3];
  strawHats[0] = new Luffy("Luffy", 120, 35, 20, 25, 50, 1500000000LL);
  strawHats[1] = new Nami("Nami", 80, 22, 12, 35, 60, 366000000LL);
  strawHats[2] = new Franky("Franky", 130, 32, 28, 18, 50, 394000000LL);

  Character *cp9[3];
  cp9[0] = new Lucci("Lucci", 150, 40, 25, 30, 60, 4000);
  cp9[1] = new Kaku("Kaku", 130, 35, 22, 28, 55, 2200);
  cp9[2] = new Kalifa("Kalifa", 95, 26, 18, 32, 50, 630);

  BattleContext context;

  ostringstream buffer;
  streambuf *old = cout.rdbuf(buffer.rdbuf());
  cout << "\n[Round 1] StrawHat attacks" << endl;
  printBeforeAfter(strawHats[0], cp9[0], "special", context);
  printBeforeAfter(strawHats[1], cp9[1], "attack", context);
  printBeforeAfter(strawHats[2], cp9[2], "special", context);

  cout << "\n[Round 2] CP9 attacks" << endl;
  printBeforeAfter(cp9[0], strawHats[0], "attack", context);
  printBeforeAfter(cp9[1], strawHats[1], "special", context);
  printBeforeAfter(cp9[2], strawHats[2], "special", context);
  cout.rdbuf(old);
  CHECK(buffer.str() ==
        "\n"
        "[Round 1] StrawHat attacks\n"
        "- Luffy special -> Lucci\n"
        "actor(before):  StrawHat[name=Luffy, hp=120, atk=35, def=20, "
        "speed=25, energy=50, bounty=1500000000] | alive=true\n"
        "target(before): CP9[name=Lucci, hp=150, atk=40, def=25, speed=30, "
        "energy=60, doriki=4000] | alive=true\n"
        "damage: 45\n"
        "actor(after):   StrawHat[name=Luffy, hp=110, atk=50, def=20, "
        "speed=40, energy=30, bounty=1500000000] | alive=true\n"
        "target(after):  CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, "
        "energy=60, doriki=4000] | alive=true\n"
        "- Nami attack -> Kaku\n"
        "actor(before):  StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, "
        "energy=60, bounty=366000000] | alive=true\n"
        "target(before): CP9[name=Kaku, hp=130, atk=35, def=22, speed=28, "
        "energy=55, doriki=2200] | alive=true\n"
        "damage: 6\n"
        "actor(after):   StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, "
        "energy=60, bounty=366000000] | alive=true\n"
        "target(after):  CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, "
        "energy=55, doriki=2200] | alive=true\n"
        "- Franky special -> Kalifa\n"
        "actor(before):  StrawHat[name=Franky, hp=130, atk=32, def=28, "
        "speed=18, energy=50, bounty=394000000] | alive=true\n"
        "target(before): CP9[name=Kalifa, hp=95, atk=26, def=18, speed=32, "
        "energy=50, doriki=630] | alive=true\n"
        "damage: 21\n"
        "actor(after):   StrawHat[name=Franky, hp=130, atk=32, def=28, "
        "speed=18, energy=20, bounty=394000000] | alive=true\n"
        "target(after):  CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, "
        "energy=50, doriki=630] | alive=true\n"
        "\n"
        "[Round 2] CP9 attacks\n"
        "- Lucci attack -> Luffy\n"
        "actor(before):  CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, "
        "energy=60, doriki=4000] | alive=true\n"
        "target(before): StrawHat[name=Luffy, hp=110, atk=50, def=20, "
        "speed=40, energy=30, bounty=1500000000] | alive=true\n"
        "damage: 220\n"
        "actor(after):   CP9[name=Lucci, hp=105, atk=40, def=25, speed=30, "
        "energy=60, doriki=4000] | alive=true\n"
        "target(after):  StrawHat[name=Luffy, hp=0, atk=50, def=20, speed=40, "
        "energy=30, bounty=1500000000] | alive=false\n"
        "- Kaku special -> Nami\n"
        "actor(before):  CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, "
        "energy=55, doriki=2200] | alive=true\n"
        "target(before): StrawHat[name=Nami, hp=80, atk=22, def=12, speed=35, "
        "energy=60, bounty=366000000] | alive=true\n"
        "damage: 69\n"
        "actor(after):   CP9[name=Kaku, hp=124, atk=35, def=22, speed=28, "
        "energy=35, doriki=2200] | alive=true\n"
        "target(after):  StrawHat[name=Nami, hp=11, atk=22, def=12, speed=35, "
        "energy=60, bounty=366000000] | alive=true\n"
        "- Kalifa special -> Franky\n"
        "actor(before):  CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, "
        "energy=50, doriki=630] | alive=true\n"
        "target(before): StrawHat[name=Franky, hp=130, atk=32, def=28, "
        "speed=18, energy=20, bounty=394000000] | alive=true\n"
        "damage: 9\n"
        "actor(after):   CP9[name=Kalifa, hp=74, atk=26, def=18, speed=32, "
        "energy=32, doriki=630] | alive=true\n"
        "target(after):  StrawHat[name=Franky, hp=121, atk=32, def=28, "
        "speed=12, energy=20, bounty=394000000] | alive=true\n");
  for (int i = 0; i < 3; i++)
    delete strawHats[i];
  for (int i = 0; i < 3; i++)
    delete cp9[i];
}

TEST_CASE("test_008") {
  Character *strawHats[4];
  strawHats[0] = new Zoro("Zoro", 110, 38, 25, 20, 45, 1111000000LL);
  strawHats[1] = new Sanji("Sanji", 100, 34, 18, 30, 45, 1032000000LL);
  strawHats[2] = new Chopper("Chopper", 90, 20, 15, 22, 55, 1000LL);
  strawHats[3] = new Usopp("Usopp", 85, 24, 14, 28, 50, 500000000LL);

  Character *cp9[4];
  cp9[0] = new Jabra("Jabra", 125, 33, 30, 24, 50, 2180);
  cp9[1] = new Blueno("Blueno", 110, 28, 24, 26, 45, 820);
  cp9[2] = new Kumadori("Kumadori", 115, 30, 20, 20, 45, 810);
  cp9[3] = new Fukurou("Fukurou", 100, 27, 16, 25, 40, 800);

  BattleContext context;

  ostringstream buffer;
  streambuf *old = cout.rdbuf(buffer.rdbuf());
  cout << "\n[Round 1] StrawHat attacks" << endl;
  printBeforeAfter(strawHats[0], cp9[0], "special", context); // Zoro -> Jabra
  printBeforeAfter(strawHats[1], cp9[1], "special", context); // Sanji -> Blueno
  printBeforeAfter(strawHats[2], cp9[2], "attack",
                   context); // Chopper -> Kumadori
  printBeforeAfter(strawHats[3], cp9[3], "special",
                   context); // Usopp -> Fukurou

  cout << "\n[Round 2] CP9 attacks" << endl;
  printBeforeAfter(cp9[0], strawHats[0], "special", context); // Jabra -> Zoro
  printBeforeAfter(cp9[1], strawHats[1], "special", context); // Blueno -> Sanji
  printBeforeAfter(cp9[2], strawHats[2], "special",
                   context); // Kumadori -> Chopper
  printBeforeAfter(cp9[3], strawHats[3], "special",
                   context); // Fukurou -> Usopp
  cout.rdbuf(old);
  CHECK(buffer.str() ==
        "\n"
        "[Round 1] StrawHat attacks\n"
        "- Zoro special -> Jabra\n"
        "actor(before):  StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, "
        "energy=45, bounty=1111000000] | alive=true\n"
        "target(before): CP9[name=Jabra, hp=125, atk=33, def=30, speed=24, "
        "energy=50, doriki=2180] | alive=true\n"
        "damage: 54\n"
        "actor(after):   StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, "
        "energy=30, bounty=1111000000] | alive=true\n"
        "target(after):  CP9[name=Jabra, hp=71, atk=33, def=30, speed=24, "
        "energy=50, doriki=2180] | alive=true\n"
        "- Sanji special -> Blueno\n"
        "actor(before):  StrawHat[name=Sanji, hp=100, atk=34, def=18, "
        "speed=30, energy=45, bounty=1032000000] | alive=true\n"
        "target(before): CP9[name=Blueno, hp=110, atk=28, def=24, speed=26, "
        "energy=45, doriki=820] | alive=true\n"
        "damage: 48\n"
        "actor(after):   StrawHat[name=Sanji, hp=100, atk=34, def=18, "
        "speed=30, energy=27, bounty=1032000000] | alive=true\n"
        "target(after):  CP9[name=Blueno, hp=62, atk=28, def=16, speed=26, "
        "energy=45, doriki=820] | alive=true\n"
        "- Chopper attack -> Kumadori\n"
        "actor(before):  StrawHat[name=Chopper, hp=90, atk=20, def=15, "
        "speed=22, energy=55, bounty=1000] | alive=true\n"
        "target(before): CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, "
        "energy=45, doriki=810] | alive=true\n"
        "damage: 0\n"
        "actor(after):   StrawHat[name=Chopper, hp=90, atk=20, def=15, "
        "speed=22, energy=55, bounty=1000] | alive=true\n"
        "target(after):  CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, "
        "energy=45, doriki=810] | alive=true\n"
        "- Usopp special -> Fukurou\n"
        "actor(before):  StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, "
        "energy=50, bounty=500000000] | alive=true\n"
        "target(before): CP9[name=Fukurou, hp=100, atk=27, def=16, speed=25, "
        "energy=40, doriki=800] | alive=true\n"
        "damage: 4\n"
        "actor(after):   StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, "
        "energy=34, bounty=500000000] | alive=true\n"
        "target(after):  CP9[name=Fukurou, hp=96, atk=27, def=16, speed=13, "
        "energy=40, doriki=800] | alive=true\n"
        "\n"
        "[Round 2] CP9 attacks\n"
        "- Jabra special -> Zoro\n"
        "actor(before):  CP9[name=Jabra, hp=71, atk=33, def=30, speed=24, "
        "energy=50, doriki=2180] | alive=true\n"
        "target(before): StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, "
        "energy=30, bounty=1111000000] | alive=true\n"
        "damage: 25\n"
        "actor(after):   CP9[name=Jabra, hp=71, atk=33, def=30, speed=24, "
        "energy=32, doriki=2180] | alive=true\n"
        "target(after):  StrawHat[name=Zoro, hp=85, atk=38, def=25, speed=20, "
        "energy=30, bounty=1111000000] | alive=true\n"
        "- Blueno special -> Sanji\n"
        "actor(before):  CP9[name=Blueno, hp=62, atk=28, def=16, speed=26, "
        "energy=45, doriki=820] | alive=true\n"
        "target(before): StrawHat[name=Sanji, hp=100, atk=34, def=18, "
        "speed=30, energy=27, bounty=1032000000] | alive=true\n"
        "damage: 39\n"
        "actor(after):   CP9[name=Blueno, hp=62, atk=28, def=16, speed=26, "
        "energy=30, doriki=820] | alive=true\n"
        "target(after):  StrawHat[name=Sanji, hp=61, atk=34, def=18, speed=30, "
        "energy=27, bounty=1032000000] | alive=true\n"
        "- Kumadori special -> Chopper\n"
        "actor(before):  CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, "
        "energy=45, doriki=810] | alive=true\n"
        "target(before): StrawHat[name=Chopper, hp=90, atk=20, def=15, "
        "speed=22, energy=55, bounty=1000] | alive=true\n"
        "damage: 96\n"
        "actor(after):   CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, "
        "energy=29, doriki=810] | alive=true\n"
        "target(after):  StrawHat[name=Chopper, hp=0, atk=20, def=15, "
        "speed=22, energy=55, bounty=1000] | alive=false\n"
        "- Fukurou special -> Usopp\n"
        "actor(before):  CP9[name=Fukurou, hp=96, atk=27, def=16, speed=13, "
        "energy=40, doriki=800] | alive=true\n"
        "target(before): StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, "
        "energy=34, bounty=500000000] | alive=true\n"
        "damage: 22\n"
        "actor(after):   CP9[name=Fukurou, hp=96, atk=27, def=16, speed=13, "
        "energy=26, doriki=800] | alive=true\n"
        "target(after):  StrawHat[name=Usopp, hp=63, atk=24, def=14, speed=28, "
        "energy=34, bounty=500000000] | alive=true\n");
  for (int i = 0; i < 4; i++)
    delete strawHats[i];
  for (int i = 0; i < 4; i++)
    delete cp9[i];
}

TEST_CASE("test_101") {
  Character *luffy = new Luffy("Luffy", 120, 20, 20, 25, 40, 1500000000LL);

  Building *buildings[5] = {new MainGate("MainGate", 35),
                            new Courthouse("Courthouse", 120),
                            new TowerOfJustice("TowerOfJustice", 150),
                            new BridgeOfHesitation("BridgeOfHesitation", 100),
                            new BusterCallShip("BusterCallShip", 180)};

  BattleContext context;
  context.busterCallTimer = 99;

  luffy->specialSkill(buildings[0], context);

  for (int turn = 0; turn < 6; turn++) {
    for (int i = 0; i < 5; i++) {
      buildings[i]->applyEffect(context);
    }
  }
  CHECK(buildings[0]->str() ==
        "Building[name=MainGate, hp=0, maxHP=35, destroyed=true]");
  CHECK(buildings[1]->str() ==
        "Building[name=Courthouse, hp=120, maxHP=120, destroyed=false]");
  CHECK(str(context) ==
        "resultCode= turnCount=0 morale=5 alarmLevel=40 rescueProgress=50 "
        "escapeProgress=0 busterCallTimer=93");

  delete luffy;
  for (int i = 0; i < 5; i++)
    delete buildings[i];
}

TEST_CASE("test_102") {
  Character *strawHats[3] = {
      new Luffy("Luffy", 120, 20, 20, 25, 40, 1500000000LL),
      new Nami("Nami", 80, 25, 12, 35, 10, 366000000LL),
      new Usopp("Usopp", 85, 25, 14, 28, 10, 500000000LL)};

  Character *cp9[1] = {new Lucci("Lucci", 80, 10, 20, 30, 0, 0)};

  Building *buildings[5] = {new MainGate("MainGate", 35),
                            new Courthouse("Courthouse", 120),
                            new TowerOfJustice("TowerOfJustice", 150),
                            new BridgeOfHesitation("BridgeOfHesitation", 100),
                            new BusterCallShip("BusterCallShip", 180)};

  BattleContext context;
  context.busterCallTimer = 99;

  // turnCount 1 morale = 5
  strawHats[0]->specialSkill(buildings[0], context);
  strawHats[0]->endTurn(context);
  for (int i = 0; i < 5; i++) {
    buildings[i]->applyEffect(context);
  }

  // turnCount 2 morale = 5
  strawHats[1]->attack(cp9[0], context);
  strawHats[1]->endTurn(context);
  for (int i = 0; i < 5; i++) {
    buildings[i]->applyEffect(context);
  }

  // turnCount 3 morale = 15
  strawHats[2]->attack(cp9[0], context);
  strawHats[2]->endTurn(context);
  for (int i = 0; i < 5; i++) {
    buildings[i]->applyEffect(context);
  }

  // turnCount 4
  cp9[0]->attack(strawHats[0], context);
  cp9[0]->endTurn(context);
  for (int i = 0; i < 5; i++) {
    buildings[i]->applyEffect(context);
  }

  // turnCount 5
  strawHats[0]->specialSkill(cp9[0], context);
  strawHats[0]->endTurn(context);
  for (int i = 0; i < 5; i++) {
    buildings[i]->applyEffect(context);
  }

  // turnCount 6 morale = 20 (already plus 5 from defeating Lucci)
  strawHats[1]->attack(cp9[0], context); 
  // REMINDER: This attack defeats Lucci but does not trigger the default +5 morale because I put the plus in processTurn
  strawHats[1]->endTurn(context);
  for (int i = 0; i < 5; i++) {
    buildings[i]->applyEffect(context);
  }

  CHECK(cp9[0]->str() ==
        "CP9[name=Lucci, hp=0, atk=10, def=20, speed=30, energy=0, doriki=0]");
  CHECK(str(context) ==
        "resultCode= turnCount=0 morale=15 alarmLevel=50 rescueProgress=50 "
        "escapeProgress=0 busterCallTimer=93");

  for (int i = 0; i < 3; i++)
    delete strawHats[i];
  for (int i = 0; i < 1; i++)
    delete cp9[i];
  for (int i = 0; i < 5; i++)
    delete buildings[i];
}

TEST_CASE("test_200a") {
  ofstream fout("test_200.txt");
  fout << "CONTEXT 0 0 0 0 99 20\n";
  fout << "STRAW_HAT Luffy 120 20 20 25 40 1500000000\n";
  fout << "STRAW_HAT Nami 80 25 12 35 10 366000000\n";
  fout << "STRAW_HAT Usopp 85 25 14 28 10 500000000\n";
  fout << "CP9 Lucci 80 10 20 30 0 0\n";
  fout << "BUILDING MainGate 35\n";
  fout << "BUILDING Courthouse 120\n";
  fout << "BUILDING TowerOfJustice 150\n";
  fout << "BUILDING BridgeOfHesitation 100\n";
  fout << "BUILDING BusterCallShip 180\n";
  fout.close();

  EniesLobbyBattle battle("test_200.txt");
  battle.runBattle();
  CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 6 20 50 50 0 93");
  remove("test_200.txt");
}
TEST_CASE("test_113")
{
    Character *test = new Zoro("test", 100, 100, 6, 0, 20, 0);
    Building *building = new MainGate("MainGate", 120);
    BattleContext context;
    CHECK(test->attack(building, context) == 102);
    test->endTurn(context);
    CHECK(test->attack(building, context) == 102);
    test->endTurn(context);
    CHECK(test->str() == "StrawHat[name=test, hp=100, atk=100, def=6, speed=0, energy=20, bounty=0]");
    CHECK(building->str() == "Building[name=MainGate, hp=0, maxHP=120, destroyed=true]");
    CHECK(str(context) == "resultCode= turnCount=0 morale=5 alarmLevel=0 rescueProgress=20 escapeProgress=0 busterCallTimer=0");

    delete test;
    delete building;
}
TEST_CASE("test_017")
{
    BattleContext ctx;
    Character *luffy = new Luffy("Luffy", 101, 103, 0, 0, 0, 0);
    Character *kabu = new Kaku("Kaku", 120, 0, 0, 0, 0, 0);
    luffy->receiveDamage(70);
    CHECK(luffy->attack(kabu, ctx) == 119);
    luffy->endTurn(ctx);
    luffy->endTurn(ctx);
    luffy->receiveDamage(1);
    CHECK(luffy->attack(kabu, ctx) == 134);
    luffy->endTurn(ctx);
    luffy->endTurn(ctx);
    CHECK(luffy->str() == "StrawHat[name=Luffy, hp=30, atk=103, def=0, speed=0, energy=0, bounty=0]");
    CHECK(kabu->str() == "CP9[name=Kaku, hp=0, atk=0, def=0, speed=0, energy=0, doriki=0]");
    // REMINDER: How the f are we supposed to check if Luffy has killed somebody purely calling endTurn
    // REMINDER: I check it in the processTurn logic
    CHECK(str(ctx) == "resultCode= turnCount=0 morale=11 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=0");

    delete luffy;
    delete kabu;
}
TEST_CASE("test_021")
{
    BattleContext ctx;
    Character *luffy = new Luffy("Luffy", 101, 103, 0, 0, 40, 0);
    Character *kabu = new Kaku("Kaku", 100, 0, 3, 0, 0, 0);
    luffy->receiveDamage(71);
    CHECK(luffy->specialSkill(kabu, ctx) == 203);
    luffy->endTurn(ctx);
    luffy->endTurn(ctx);
    // REMINDER: Same as test_017
    CHECK(luffy->str() == "StrawHat[name=Luffy, hp=21, atk=118, def=0, speed=15, energy=20, bounty=0]");
    CHECK(kabu->str() == "CP9[name=Kaku, hp=0, atk=0, def=3, speed=0, energy=0, doriki=0]");
    CHECK(str(ctx) == "resultCode= turnCount=0 morale=6 alarmLevel=10 rescueProgress=0 escapeProgress=0 busterCallTimer=0");

    delete luffy;
    delete kabu;
}
TEST_CASE("test_034")
{
    BattleContext ctx;
    Character *sanji = new Sanji("Sanji", 101, 103, 2, 51, 0, 0);
    Character *kabu = new Kaku("Kaku", 200, 0, 1, 0, 0, 0);
    CHECK(sanji->attack(kabu, ctx) == 141);
    sanji->endTurn(ctx);
    CHECK(sanji->str() == "StrawHat[name=Sanji, hp=101, atk=103, def=2, speed=51, energy=0, bounty=0]");
    CHECK(kabu->str() == "CP9[name=Kaku, hp=59, atk=0, def=1, speed=0, energy=0, doriki=0]");
    CHECK(str(ctx) == "resultCode= turnCount=0 morale=0 alarmLevel=0 rescueProgress=0 escapeProgress=0 busterCallTimer=0");

    delete sanji;
    delete kabu;
}
TEST_CASE("test_008")
{
    Character *strawHats[4];
    strawHats[0] = new Zoro("Zoro", 110, 38, 25, 20, 45, 1111000000LL);
    strawHats[1] = new Sanji("Sanji", 100, 34, 18, 30, 45, 1032000000LL);
    strawHats[2] = new Chopper("Chopper", 90, 20, 15, 22, 55, 1000LL);
    strawHats[3] = new Usopp("Usopp", 85, 24, 14, 28, 50, 500000000LL);

    Character *cp9[4];
    cp9[0] = new Jabra("Jabra", 125, 33, 30, 24, 50, 2180);
    cp9[1] = new Blueno("Blueno", 110, 28, 24, 26, 45, 820);
    cp9[2] = new Kumadori("Kumadori", 115, 30, 20, 20, 45, 810);
    cp9[3] = new Fukurou("Fukurou", 100, 27, 16, 25, 40, 800);

    BattleContext context;

    ostringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());
    cout << "\n[Round 1] StrawHat attacks" << endl;
    printBeforeAfter(strawHats[0], cp9[0], "special", context); // Zoro -> Jabra
    printBeforeAfter(strawHats[1], cp9[1], "special", context); // Sanji -> Blueno
    printBeforeAfter(strawHats[2], cp9[2], "attack", context);  // Chopper -> Kumadori
    printBeforeAfter(strawHats[3], cp9[3], "special", context); // Usopp -> Fukurou

    cout << "\n[Round 2] CP9 attacks" << endl;
    printBeforeAfter(cp9[0], strawHats[0], "special", context); // Jabra -> Zoro
    printBeforeAfter(cp9[1], strawHats[1], "special", context); // Blueno -> Sanji
    printBeforeAfter(cp9[2], strawHats[2], "special", context); // Kumadori -> Chopper
    printBeforeAfter(cp9[3], strawHats[3], "special", context); // Fukurou -> Usopp
    cout.rdbuf(old);
    CHECK(buffer.str() == "\n"
                          "[Round 1] StrawHat attacks\n"
                          "- Zoro special -> Jabra\n"
                          "actor(before):  StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, energy=45, bounty=1111000000] | alive=true\n"
                          "target(before): CP9[name=Jabra, hp=125, atk=33, def=30, speed=24, energy=50, doriki=2180] | alive=true\n"
                          "damage: 54\n"
                          "actor(after):   StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, energy=30, bounty=1111000000] | alive=true\n"
                          "target(after):  CP9[name=Jabra, hp=71, atk=33, def=30, speed=24, energy=50, doriki=2180] | alive=true\n"
                          "- Sanji special -> Blueno\n"
                          "actor(before):  StrawHat[name=Sanji, hp=100, atk=34, def=18, speed=30, energy=45, bounty=1032000000] | alive=true\n"
                          "target(before): CP9[name=Blueno, hp=110, atk=28, def=24, speed=26, energy=45, doriki=820] | alive=true\n"
                          "damage: 48\n"
                          "actor(after):   StrawHat[name=Sanji, hp=100, atk=34, def=18, speed=30, energy=27, bounty=1032000000] | alive=true\n"
                          "target(after):  CP9[name=Blueno, hp=62, atk=28, def=16, speed=26, energy=45, doriki=820] | alive=true\n"
                          "- Chopper attack -> Kumadori\n"
                          "actor(before):  StrawHat[name=Chopper, hp=90, atk=20, def=15, speed=22, energy=55, bounty=1000] | alive=true\n"
                          "target(before): CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, energy=45, doriki=810] | alive=true\n"
                          "damage: 0\n"
                          "actor(after):   StrawHat[name=Chopper, hp=90, atk=20, def=15, speed=22, energy=55, bounty=1000] | alive=true\n"
                          "target(after):  CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, energy=45, doriki=810] | alive=true\n"
                          "- Usopp special -> Fukurou\n"
                          "actor(before):  StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, energy=50, bounty=500000000] | alive=true\n"
                          "target(before): CP9[name=Fukurou, hp=100, atk=27, def=16, speed=25, energy=40, doriki=800] | alive=true\n"
                          "damage: 4\n"
                          "actor(after):   StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, energy=34, bounty=500000000] | alive=true\n"
                          "target(after):  CP9[name=Fukurou, hp=96, atk=27, def=16, speed=13, energy=40, doriki=800] | alive=true\n"
                          "\n"
                          "[Round 2] CP9 attacks\n"
                          "- Jabra special -> Zoro\n"
                          "actor(before):  CP9[name=Jabra, hp=71, atk=33, def=30, speed=24, energy=50, doriki=2180] | alive=true\n"
                          "target(before): StrawHat[name=Zoro, hp=110, atk=38, def=25, speed=20, energy=30, bounty=1111000000] | alive=true\n"
                          "damage: 25\n"
                          "actor(after):   CP9[name=Jabra, hp=71, atk=33, def=30, speed=24, energy=32, doriki=2180] | alive=true\n"
                          "target(after):  StrawHat[name=Zoro, hp=85, atk=38, def=25, speed=20, energy=30, bounty=1111000000] | alive=true\n"
                          "- Blueno special -> Sanji\n"
                          "actor(before):  CP9[name=Blueno, hp=62, atk=28, def=16, speed=26, energy=45, doriki=820] | alive=true\n"
                          "target(before): StrawHat[name=Sanji, hp=100, atk=34, def=18, speed=30, energy=27, bounty=1032000000] | alive=true\n"
                          "damage: 39\n"
                          "actor(after):   CP9[name=Blueno, hp=62, atk=28, def=16, speed=26, energy=30, doriki=820] | alive=true\n"
                          "target(after):  StrawHat[name=Sanji, hp=61, atk=34, def=18, speed=30, energy=27, bounty=1032000000] | alive=true\n"
                          "- Kumadori special -> Chopper\n"
                          "actor(before):  CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, energy=45, doriki=810] | alive=true\n"
                          "target(before): StrawHat[name=Chopper, hp=90, atk=20, def=15, speed=22, energy=55, bounty=1000] | alive=true\n"
                          "damage: 96\n"
                          "actor(after):   CP9[name=Kumadori, hp=115, atk=30, def=20, speed=20, energy=29, doriki=810] | alive=true\n"
                          "target(after):  StrawHat[name=Chopper, hp=0, atk=20, def=15, speed=22, energy=55, bounty=1000] | alive=false\n"
                          "- Fukurou special -> Usopp\n"
                          "actor(before):  CP9[name=Fukurou, hp=96, atk=27, def=16, speed=13, energy=40, doriki=800] | alive=true\n"
                          "target(before): StrawHat[name=Usopp, hp=85, atk=24, def=14, speed=28, energy=34, bounty=500000000] | alive=true\n"
                          "damage: 22\n"
                          "actor(after):   CP9[name=Fukurou, hp=96, atk=27, def=16, speed=13, energy=26, doriki=800] | alive=true\n"
                          "target(after):  StrawHat[name=Usopp, hp=63, atk=24, def=14, speed=28, energy=34, bounty=500000000] | alive=true\n");
    for (int i = 0; i < 4; i++)
        delete strawHats[i];
    for (int i = 0; i < 4; i++)
        delete cp9[i];
}
TEST_CASE("test_200b") {
  ofstream fout("test.txt");
fout << "CP9 Kumadori 113 54 19 49 74 4195\n";
fout << "STRAW_HAT Usopp 66 26 8 16 60 615857740\n";
fout << "CP9 Kaku 129 54 15 32 40 3084\n";
fout << "CP9 Jabra 133 39 20 10 53 2393\n";
fout << "BUILDING MainGate 101\n";
fout << "BUILDING BusterCallShip 108\n";
fout << "CP9 Fukurou 92 40 32 39 40 3124\n";
fout << "CONTEXT 61 78 26 33 14 67\n";
fout << "BUILDING BridgeOfHesitation 245\n";
fout << "STRAW_HAT Chopper 180 93 28 20 59 337807167\n";
fout << "CP9 Blueno 89 27 33 24 55 2368\n";
fout << "STRAW_HAT Zoro 70 70 17 29 79 306108629\n";
fout << "CP9 Kalifa 82 41 22 27 35 4657\n";
fout << "BUILDING Courthouse 101\n";
fout << "STRAW_HAT Luffy 76 100 23 18 63 618673614\n";
fout << "CP9 Lucci 115 32 21 33 30 3195\n";
fout << "STRAW_HAT Franky 139 40 5 20 53 601088688\n";
fout << "BUILDING TowerOfJustice 172\n";
fout << "STRAW_HAT Sanji 155 97 27 24 60 613351765\n";
fout << "STRAW_HAT Nami 185 63 33 11 53 536681840\n";
fout.close();
  EniesLobbyBattle battle("test.txt");
  battle.runBattle();
  CHECK(battle.getResult() == "BUSTER_CALL 15 71 78 100 51 0");
  // REMINDER: Is this case correct? alarmLevel only increase / decrease in multiples of 5
  remove("test.txt");
}
TEST_CASE("test_custom_random_21")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 165\n";
    fout << "BUILDING BusterCallShip 204\n";
    fout << "CP9 Kalifa 128 44 21 57 39 849302154\n";
    fout << "STRAW_HAT Usopp 102 91 16 38 65 294850173\n";
    fout << "STRAW_HAT Sanji 147 26 43 12 52 602948153\n";
    fout << "BUILDING BridgeOfHesitation 131\n";
    fout << "CP9 Kaku 156 37 11 49 70 930582147\n";
    fout << "BUILDING TowerOfJustice 188\n";
    fout << "STRAW_HAT Luffy 95 64 34 23 48 384920157\n";
    fout << "STRAW_HAT Zoro 172 50 50 15 79 719482053\n";
    fout << "STRAW_HAT Chopper 119 85 19 60 41 4029\n";
    fout << "STRAW_HAT Franky 138 18 28 32 56 2740\n";
    fout << "STRAW_HAT Nami 144 55 37 41 54 4920\n";
    fout << "CP9 Lucci 105 43 20 47 63 1843\n";
    fout << "BUILDING MainGate 222\n";
    fout << "CP9 Blueno 162 53 14 28 42 3759\n";
    fout << "CP9 Jabra 150 31 46 55 33 2090\n";
    fout << "CP9 Fukurou 83 76 11 17 74 3194\n";
    fout << "CP9 Kumadori 114 22 29 60 51 3594\n";
    fout << "CONTEXT 32 84 47 91 55 63\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 10 49 75 100 100 46");
    remove("test.txt");
}

TEST_CASE("test_custom_random_22")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 199\n";
    fout << "BUILDING BusterCallShip 115\n";
    fout << "CP9 Kalifa 142 53 14 22 66 719483025\n";
    fout << "STRAW_HAT Usopp 122 19 29 57 71 384029157\n";
    fout << "STRAW_HAT Sanji 175 42 41 30 50 104928374\n";
    fout << "BUILDING BridgeOfHesitation 189\n";
    fout << "CP9 Kaku 106 47 37 49 38 930481572\n";
    fout << "BUILDING TowerOfJustice 116\n";
    fout << "STRAW_HAT Luffy 159 36 22 15 54 502941837\n";
    fout << "STRAW_HAT Zoro 94 58 26 33 45 401928473\n";
    fout << "STRAW_HAT Chopper 173 41 42 56 31 829501473\n";
    fout << "STRAW_HAT Franky 111 96 15 18 73 602948371\n";
    fout << "STRAW_HAT Nami 134 29 48 44 60 1958\n";
    fout << "CP9 Lucci 156 64 30 12 55 3104\n";
    fout << "BUILDING MainGate 182\n";
    fout << "CP9 Blueno 147 50 50 27 79 2749\n";
    fout << "CP9 Jabra 128 85 11 60 48 3840\n";
    fout << "CP9 Fukurou 99 78 19 39 67 1937\n";
    fout << "CP9 Kumadori 144 23 34 51 42 4829\n";
    fout << "CONTEXT 91 46 58 62 34 77\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 79 56 100 100 21");
    remove("test.txt");
}

TEST_CASE("test_custom_random_23")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 148\n";
    fout << "BUILDING BusterCallShip 234\n";
    fout << "CP9 Kalifa 158 55 50 13 74 384029154\n";
    fout << "STRAW_HAT Usopp 86 95 23 37 50 719483026\n";
    fout << "STRAW_HAT Sanji 133 30 33 58 42 502948173\n";
    fout << "BUILDING BridgeOfHesitation 157\n";
    fout << "CP9 Kaku 177 47 14 21 65 2749\n";
    fout << "BUILDING TowerOfJustice 134\n";
    fout << "STRAW_HAT Luffy 152 44 19 60 53 930481275\n";
    fout << "STRAW_HAT Zoro 121 73 34 25 77 472910485\n";
    fout << "STRAW_HAT Chopper 194 36 46 41 39 104928375\n";
    fout << "STRAW_HAT Franky 116 51 11 16 68 602941837\n";
    fout << "STRAW_HAT Nami 140 88 28 54 46 829501472\n";
    fout << "CP9 Lucci 171 19 40 32 62 4103\n";
    fout << "BUILDING MainGate 249\n";
    fout << "CP9 Blueno 103 62 15 47 31 1958\n";
    fout << "CP9 Jabra 125 58 27 49 57 3194\n";
    fout << "CP9 Fukurou 149 24 42 33 35 3847\n";
    fout << "CP9 Kumadori 92 41 49 11 79 4830\n";
    fout << "CONTEXT 44 79 36 83 61 52\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 46 75 100 100 48");
    remove("test.txt");
}

TEST_CASE("test_custom_random_24")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 216\n";
    fout << "BUILDING BusterCallShip 171\n";
    fout << "CP9 Kalifa 134 49 15 58 79 184930275\n";
    fout << "STRAW_HAT Usopp 141 38 18 47 36 620584913\n";
    fout << "STRAW_HAT Sanji 164 21 46 25 71 472910583\n";
    fout << "BUILDING BridgeOfHesitation 233\n";
    fout << "CP9 Kaku 98 55 34 33 53 1930\n";
    fout << "BUILDING TowerOfJustice 187\n";
    fout << "STRAW_HAT Luffy 113 27 50 36 66 294850173\n";
    fout << "STRAW_HAT Zoro 149 91 16 57 41 719402853\n";
    fout << "STRAW_HAT Chopper 82 59 33 14 78 502914837\n";
    fout << "STRAW_HAT Franky 155 46 22 43 49 930482516\n";
    fout << "STRAW_HAT Nami 176 34 45 19 55 384920516\n";
    fout << "CP9 Lucci 127 76 11 52 32 3752\n";
    fout << "BUILDING MainGate 104\n";
    fout << "CP9 Blueno 191 50 29 26 73 2749\n";
    fout << "CP9 Jabra 122 64 41 12 57 3847\n";
    fout << "CP9 Fukurou 138 43 38 60 60 4829\n";
    fout << "CP9 Kumadori 109 82 14 31 44 4829\n";
    fout << "CONTEXT 54 28 67 43 49 81\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 15 45 38 100 100 35");
    remove("test.txt");
}

TEST_CASE("test_custom_random_25")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 129\n";
    fout << "BUILDING BusterCallShip 192\n";
    fout << "CP9 Kalifa 157 47 18 21 38 194850273\n";
    fout << "STRAW_HAT Usopp 121 92 31 53 44 483920154\n";
    fout << "STRAW_HAT Sanji 173 50 50 42 70 582910473\n";
    fout << "BUILDING BridgeOfHesitation 169\n";
    fout << "CP9 Kaku 149 53 41 22 68 3105\n";
    fout << "BUILDING TowerOfJustice 136\n";
    fout << "STRAW_HAT Luffy 164 43 14 49 52 639205814\n";
    fout << "STRAW_HAT Zoro 108 76 46 27 76 295018473\n";
    fout << "STRAW_HAT Chopper 153 29 25 58 41 710492835\n";
    fout << "STRAW_HAT Franky 129 57 38 16 65 2184\n";
    fout << "STRAW_HAT Nami 114 23 15 45 47 4739\n";
    fout << "CP9 Lucci 187 88 19 60 33 1958\n";
    fout << "BUILDING MainGate 252\n";
    fout << "CP9 Blueno 94 61 32 13 78 3925\n";
    fout << "CP9 Jabra 145 35 11 36 59 2847\n";
    fout << "CP9 Fukurou 82 15 27 30 61 2847\n";
    fout << "CP9 Kumadori 138 39 33 55 55 2184\n";
    fout << "CONTEXT 71 52 44 60 83 36\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 17 73 62 100 100 67");
    remove("test.txt");
}

TEST_CASE("test_custom_random_26")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 241\n";
    fout << "BUILDING BusterCallShip 154\n";
    fout << "CP9 Kalifa 134 53 14 38 45 291503847\n";
    fout << "STRAW_HAT Usopp 211 17 29 55 52 601928475\n";
    fout << "STRAW_HAT Sanji 127 50 35 14 74 539201847\n";
    fout << "BUILDING BridgeOfHesitation 211\n";
    fout << "CP9 Kaku 193 91 17 48 31 3029\n";
    fout << "BUILDING TowerOfJustice 179\n";
    fout << "STRAW_HAT Luffy 156 33 49 46 66 915830247\n";
    fout << "STRAW_HAT Zoro 106 64 22 43 53 342910586\n";
    fout << "STRAW_HAT Chopper 118 47 26 11 57 825491036\n";
    fout << "STRAW_HAT Franky 178 26 12 60 78 205847193\n";
    fout << "STRAW_HAT Nami 142 58 16 32 42 471029385\n";
    fout << "CP9 Lucci 88 44 11 25 63 2847\n";
    fout << "BUILDING MainGate 147\n";
    fout << "CP9 Blueno 139 73 38 17 40 4192\n";
    fout << "CP9 Jabra 150 29 41 15 48 4930\n";
    fout << "CP9 Fukurou 121 21 29 55 52 1845\n";
    fout << "CP9 Kumadori 94 85 15 30 35 1956\n";
    fout << "CONTEXT 76 33 94 51 62 48\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 12 82 43 100 100 51");
    remove("test.txt");
}

TEST_CASE("test_custom_random_27")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 103\n";
    fout << "BUILDING BusterCallShip 186\n";
    fout << "CP9 Kalifa 157 37 14 60 51 384729104\n";
    fout << "STRAW_HAT Usopp 114 93 49 28 42 502419385\n";
    fout << "STRAW_HAT Sanji 158 55 37 23 48 719402563\n";
    fout << "BUILDING BridgeOfHesitation 158\n";
    fout << "CP9 Kaku 144 34 46 32 56 2748\n";
    fout << "BUILDING TowerOfJustice 224\n";
    fout << "STRAW_HAT Luffy 119 76 11 57 33 620584719\n";
    fout << "STRAW_HAT Zoro 150 18 28 41 54 315482960\n";
    fout << "STRAW_HAT Chopper 125 31 46 17 55 845291307\n";
    fout << "STRAW_HAT Franky 111 61 25 13 77 194850372\n";
    fout << "STRAW_HAT Nami 136 49 31 52 59 519300000\n";
    fout << "CP9 Lucci 105 85 16 44 38 1952\n";
    fout << "BUILDING MainGate 183\n";
    fout << "CP9 Blueno 162 22 43 19 70 4310\n";
    fout << "CP9 Jabra 101 55 37 23 48 3824\n";
    fout << "CP9 Fukurou 138 43 20 47 63 2740\n";
    fout << "CP9 Kumadori 83 50 33 15 79 3594\n";
    fout << "CONTEXT 62 38 74 51 44 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 12 74 48 100 100 33");
    remove("test.txt");
}

TEST_CASE("test_custom_random_28")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 192\n";
    fout << "BUILDING BusterCallShip 137\n";
    fout << "CP9 Kalifa 150 29 41 15 48 104928475\n";
    fout << "STRAW_HAT Usopp 121 21 29 55 52 930582147\n";
    fout << "STRAW_HAT Sanji 175 37 33 52 69 384920157\n";
    fout << "BUILDING BridgeOfHesitation 118\n";
    fout << "CP9 Kaku 94 85 15 30 35 3194\n";
    fout << "BUILDING TowerOfJustice 178\n";
    fout << "STRAW_HAT Luffy 142 58 16 32 42 294850173\n";
    fout << "STRAW_HAT Zoro 88 44 11 25 63 602948153\n";
    fout << "STRAW_HAT Chopper 139 73 38 17 40 849302154\n";
    fout << "STRAW_HAT Franky 239 18 28 41 54 4920\n";
    fout << "STRAW_HAT Nami 134 53 14 38 45 2740\n";
    fout << "CP9 Lucci 211 17 29 55 52 1843\n";
    fout << "BUILDING MainGate 121\n";
    fout << "CP9 Blueno 127 50 35 14 74 3759\n";
    fout << "CP9 Jabra 193 91 17 48 31 4029\n";
    fout << "CP9 Fukurou 156 33 49 46 66 2090\n";
    fout << "CP9 Kumadori 106 64 22 43 53 3594\n";
    fout << "CONTEXT 94 51 62 48 76 33\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 33 53 56 100 56 45");
    remove("test.txt");
}

TEST_CASE("test_custom_random_29")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 155\n";
    fout << "BUILDING BusterCallShip 243\n";
    fout << "CP9 Kalifa 147 50 50 27 79 291503847\n";
    fout << "STRAW_HAT Usopp 128 85 11 60 48 601928475\n";
    fout << "STRAW_HAT Sanji 99 78 19 39 67 342910586\n";
    fout << "BUILDING BridgeOfHesitation 144\n";
    fout << "CP9 Kaku 182 23 34 51 42 1845\n";
    fout << "BUILDING TowerOfJustice 237\n";
    fout << "STRAW_HAT Luffy 94 58 26 33 45 825491036\n";
    fout << "STRAW_HAT Zoro 173 41 42 56 31 471029385\n";
    fout << "STRAW_HAT Chopper 111 96 15 18 73 915830247\n";
    fout << "STRAW_HAT Franky 134 29 48 44 60 205847193\n";
    fout << "STRAW_HAT Nami 156 64 30 12 55 539201847\n";
    fout << "CP9 Lucci 159 36 22 15 54 4192\n";
    fout << "BUILDING MainGate 106\n";
    fout << "CP9 Blueno 106 47 37 49 38 3029\n";
    fout << "CP9 Jabra 142 53 14 22 66 2847\n";
    fout << "CP9 Fukurou 122 19 29 57 71 4930\n";
    fout << "CP9 Kumadori 175 42 41 30 50 1956\n";
    fout << "CONTEXT 46 58 62 34 77 91\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 52 43 48 100 42 28");
    remove("test.txt");
}

TEST_CASE("test_custom_random_30")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 202\n";
    fout << "BUILDING BusterCallShip 166\n";
    fout << "CP9 Kalifa 116 51 11 16 68 738492015\n";
    fout << "STRAW_HAT Usopp 140 88 28 54 46 194850273\n";
    fout << "STRAW_HAT Sanji 171 19 40 32 62 820491385\n";
    fout << "BUILDING BridgeOfHesitation 134\n";
    fout << "CP9 Kaku 103 62 15 47 31 3925\n";
    fout << "BUILDING TowerOfJustice 249\n";
    fout << "STRAW_HAT Luffy 152 44 19 60 53 582910473\n";
    fout << "STRAW_HAT Zoro 121 73 34 25 77 295018473\n";
    fout << "STRAW_HAT Chopper 194 36 46 41 39 483920154\n";
    fout << "STRAW_HAT Franky 158 55 50 13 74 710492835\n";
    fout << "STRAW_HAT Nami 86 95 23 37 50 639205814\n";
    fout << "CP9 Lucci 133 30 33 58 42 2184\n";
    fout << "BUILDING MainGate 157\n";
    fout << "CP9 Blueno 177 47 14 21 65 4739\n";
    fout << "CP9 Jabra 125 58 27 49 57 3105\n";
    fout << "CP9 Fukurou 149 24 42 33 35 1958\n";
    fout << "CP9 Kumadori 92 41 49 11 79 2847\n";
    fout << "CONTEXT 79 36 83 61 52 44\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 44 82 51 100 84 10");
    remove("test.txt");
}
TEST_CASE("test_custom_random_31")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 104\n";
    fout << "BUILDING BusterCallShip 173\n";
    fout << "CP9 Kalifa 127 76 11 52 32 930482516\n";
    fout << "STRAW_HAT Usopp 191 50 29 26 73 384920516\n";
    fout << "STRAW_HAT Sanji 138 43 38 60 60 184930275\n";
    fout << "CP9 Kaku 109 82 14 31 44 620584913\n";
    fout << "BUILDING TowerOfJustice 187\n";
    fout << "STRAW_HAT Luffy 113 27 50 36 66 472910583\n";
    fout << "STRAW_HAT Zoro 149 91 16 57 41 294850173\n";
    fout << "STRAW_HAT Chopper 82 59 33 14 78 719402853\n";
    fout << "STRAW_HAT Franky 176 34 45 19 55 502914837\n";
    fout << "STRAW_HAT Nami 122 64 41 12 57 1930\n";
    fout << "CP9 Lucci 155 46 22 43 49 3752\n";
    fout << "BUILDING MainGate 113\n";
    fout << "CP9 Blueno 98 55 34 33 53 2749\n";
    fout << "CP9 Jabra 134 49 15 58 79 3847\n";
    fout << "CP9 Fukurou 141 38 18 47 36 4829\n";
    fout << "CP9 Kumadori 164 21 46 25 71 4829\n";
    fout << "CONTEXT 28 67 43 49 81 54\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 38 35 57 100 57 46");
    remove("test.txt");
}

TEST_CASE("test_custom_random_32")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 252\n";
    fout << "BUILDING BusterCallShip 194\n";
    fout << "CP9 Kalifa 145 35 11 36 59 639205814\n";
    fout << "STRAW_HAT Usopp 121 92 31 53 44 295018473\n";
    fout << "STRAW_HAT Sanji 173 50 50 42 70 710492835\n";
    fout << "BUILDING BridgeOfHesitation 169\n";
    fout << "CP9 Kaku 114 23 15 45 47 2184\n";
    fout << "BUILDING TowerOfJustice 136\n";
    fout << "STRAW_HAT Luffy 164 43 14 49 52 820491385\n";
    fout << "STRAW_HAT Zoro 108 76 46 27 76 738492015\n";
    fout << "STRAW_HAT Chopper 153 29 25 58 41 194850273\n";
    fout << "STRAW_HAT Franky 187 88 19 60 33 483920154\n";
    fout << "STRAW_HAT Nami 94 61 32 13 78 582910473\n";
    fout << "CP9 Lucci 149 53 41 22 68 3105\n";
    fout << "BUILDING MainGate 122\n";
    fout << "CP9 Blueno 82 15 27 30 61 4739\n";
    fout << "CP9 Jabra 138 39 33 55 55 1958\n";
    fout << "CP9 Fukurou 157 47 18 21 38 3925\n";
    fout << "CP9 Kumadori 129 57 38 16 65 2847\n";
    fout << "CONTEXT 52 44 60 83 36 71\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 56 44 44 100 91 8");
    remove("test.txt");
}

TEST_CASE("test_custom_random_33")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 179\n";
    fout << "BUILDING BusterCallShip 122\n";
    fout << "CP9 Kalifa 139 73 38 17 40 539201847\n";
    fout << "STRAW_HAT Usopp 150 29 41 15 48 205847193\n";
    fout << "STRAW_HAT Sanji 121 21 29 55 52 915830247\n";
    fout << "CP9 Kaku 175 37 33 52 69 3029\n";
    fout << "BUILDING TowerOfJustice 147\n";
    fout << "STRAW_HAT Luffy 127 50 35 14 74 342910586\n";
    fout << "STRAW_HAT Zoro 193 91 17 48 31 825491036\n";
    fout << "STRAW_HAT Chopper 156 33 49 46 66 291503847\n";
    fout << "STRAW_HAT Franky 118 47 26 11 57 601928475\n";
    fout << "STRAW_HAT Nami 178 26 12 60 78 471029385\n";
    fout << "CP9 Lucci 142 58 16 32 42 2847\n";
    fout << "BUILDING MainGate 211\n";
    fout << "CP9 Blueno 88 44 11 25 63 4192\n";
    fout << "CP9 Jabra 94 85 15 30 35 4930\n";
    fout << "CP9 Fukurou 134 53 14 38 45 1845\n";
    fout << "CP9 Kumadori 106 64 22 43 53 1956\n";
    fout << "CONTEXT 33 94 51 62 48 76\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 41 34 65 100 70 10");
    remove("test.txt");
}

TEST_CASE("test_custom_random_34")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 142\n";
    fout << "BUILDING BusterCallShip 114\n";
    fout << "CP9 Kalifa 162 22 43 19 70 620584719\n";
    fout << "STRAW_HAT Usopp 111 61 25 13 77 315482960\n";
    fout << "STRAW_HAT Sanji 136 49 31 52 59 845291307\n";
    fout << "CP9 Kaku 105 85 16 44 38 2748\n";
    fout << "BUILDING TowerOfJustice 248\n";
    fout << "STRAW_HAT Luffy 138 43 20 47 63 719402563\n";
    fout << "STRAW_HAT Zoro 83 50 33 15 79 502419385\n";
    fout << "STRAW_HAT Chopper 191 27 18 53 45 384729104\n";
    fout << "STRAW_HAT Franky 125 31 46 17 55 194850372\n";
    fout << "STRAW_HAT Nami 144 34 46 32 56 519300000\n";
    fout << "CP9 Lucci 119 76 11 57 33 1952\n";
    fout << "BUILDING MainGate 105\n";
    fout << "CP9 Blueno 150 18 28 41 54 4310\n";
    fout << "CP9 Jabra 158 55 37 23 48 3824\n";
    fout << "CP9 Fukurou 157 37 14 60 51 2740\n";
    fout << "CP9 Kumadori 114 93 49 28 42 3594\n";
    fout << "CONTEXT 62 38 74 51 44 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 38 28 43 100 59 8");
    remove("test.txt");
}

TEST_CASE("test_custom_random_35")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 239\n";
    fout << "BUILDING BusterCallShip 106\n";
    fout << "CP9 Kalifa 193 91 17 48 31 104928475\n";
    fout << "STRAW_HAT Usopp 156 33 49 46 66 930582147\n";
    fout << "STRAW_HAT Sanji 118 47 26 11 57 384920157\n";
    fout << "CP9 Kaku 178 26 12 60 78 3194\n";
    fout << "BUILDING TowerOfJustice 147\n";
    fout << "STRAW_HAT Luffy 142 58 16 32 42 294850173\n";
    fout << "STRAW_HAT Zoro 88 44 11 25 63 602948153\n";
    fout << "STRAW_HAT Chopper 139 73 38 17 40 849302154\n";
    fout << "STRAW_HAT Franky 150 29 41 15 48 4920\n";
    fout << "STRAW_HAT Nami 121 21 29 55 52 2740\n";
    fout << "CP9 Lucci 175 37 33 52 69 1843\n";
    fout << "BUILDING MainGate 118\n";
    fout << "CP9 Blueno 94 85 15 30 35 3759\n";
    fout << "CP9 Jabra 211 17 29 55 52 4029\n";
    fout << "CP9 Fukurou 106 64 22 43 53 2090\n";
    fout << "CP9 Kumadori 127 50 35 14 74 3594\n";
    fout << "CONTEXT 94 51 62 48 76 33\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 33 55 56 100 56 45");
    remove("test.txt");
}

TEST_CASE("test_custom_random_36")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 116\n";
    fout << "BUILDING BusterCallShip 182\n";
    fout << "CP9 Kalifa 134 29 48 44 60 291503847\n";
    fout << "STRAW_HAT Usopp 156 64 30 12 55 601928475\n";
    fout << "STRAW_HAT Sanji 147 50 50 27 79 539201847\n";
    fout << "CP9 Kaku 128 85 11 60 48 3029\n";
    fout << "BUILDING TowerOfJustice 211\n";
    fout << "STRAW_HAT Luffy 144 42 41 30 50 342910586\n";
    fout << "STRAW_HAT Zoro 94 58 26 33 45 825491036\n";
    fout << "STRAW_HAT Chopper 173 41 42 56 31 471029385\n";
    fout << "STRAW_HAT Franky 111 96 15 18 73 205847193\n";
    fout << "STRAW_HAT Nami 159 36 22 15 54 915830247\n";
    fout << "CP9 Lucci 99 78 19 39 67 2847\n";
    fout << "BUILDING MainGate 144\n";
    fout << "CP9 Blueno 106 47 37 49 38 4192\n";
    fout << "CP9 Jabra 142 53 14 22 66 4930\n";
    fout << "CP9 Fukurou 122 19 29 57 71 1845\n";
    fout << "CP9 Kumadori 237 23 34 51 42 1956\n";
    fout << "CONTEXT 46 58 62 34 77 91\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 80 48 48 100 42 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_37")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 134\n";
    fout << "BUILDING BusterCallShip 152\n";
    fout << "CP9 Kalifa 140 88 28 54 46 384729104\n";
    fout << "STRAW_HAT Usopp 171 19 40 32 62 502419385\n";
    fout << "CP9 Kaku 86 95 23 37 50 2748\n";
    fout << "BUILDING TowerOfJustice 249\n";
    fout << "STRAW_HAT Luffy 133 30 33 58 42 620584719\n";
    fout << "STRAW_HAT Zoro 177 47 14 21 65 315482960\n";
    fout << "STRAW_HAT Chopper 125 58 27 49 57 845291307\n";
    fout << "STRAW_HAT Franky 149 24 42 33 35 194850372\n";
    fout << "STRAW_HAT Nami 92 41 49 11 79 519300000\n";
    fout << "CP9 Lucci 103 62 15 47 31 1952\n";
    fout << "BUILDING MainGate 225\n";
    fout << "CP9 Blueno 194 36 46 41 39 4310\n";
    fout << "CP9 Jabra 116 51 11 16 68 3824\n";
    fout << "CP9 Fukurou 121 73 34 25 77 2740\n";
    fout << "CP9 Kumadori 163 44 19 60 53 3594\n";
    fout << "CONTEXT 79 36 83 61 52 44\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 22 53 75 100 69 32");
    remove("test.txt");
}

TEST_CASE("test_custom_random_38")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 233\n";
    fout << "BUILDING BusterCallShip 113\n";
    fout << "CP9 Kalifa 113 27 50 36 66 104928475\n";
    fout << "STRAW_HAT Usopp 149 91 16 57 41 930582147\n";
    fout << "STRAW_HAT Sanji 82 59 33 14 78 384920157\n";
    fout << "BUILDING BridgeOfHesitation 173\n";
    fout << "CP9 Kaku 176 34 45 19 55 3194\n";
    fout << "BUILDING TowerOfJustice 218\n";
    fout << "STRAW_HAT Luffy 127 76 11 52 32 294850173\n";
    fout << "STRAW_HAT Zoro 191 50 29 26 73 602948153\n";
    fout << "STRAW_HAT Chopper 138 43 38 60 60 849302154\n";
    fout << "STRAW_HAT Franky 109 82 14 31 44 4920\n";
    fout << "STRAW_HAT Nami 134 49 15 58 79 2740\n";
    fout << "CP9 Lucci 141 38 18 47 36 1843\n";
    fout << "BUILDING MainGate 187\n";
    fout << "CP9 Blueno 164 21 46 25 71 3759\n";
    fout << "CP9 Jabra 98 55 34 33 53 4029\n";
    fout << "CP9 Fukurou 122 64 41 12 57 2090\n";
    fout << "CP9 Kumadori 155 46 22 43 49 3594\n";
    fout << "CONTEXT 54 28 67 43 49 81\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 50 38 100 100 36");
    remove("test.txt");
}

TEST_CASE("test_custom_random_39")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 122\n";
    fout << "BUILDING BusterCallShip 169\n";
    fout << "CP9 Kalifa 164 43 14 49 52 291503847\n";
    fout << "STRAW_HAT Usopp 108 76 46 27 76 601928475\n";
    fout << "STRAW_HAT Sanji 153 29 25 58 41 539201847\n";
    fout << "BUILDING BridgeOfHesitation 129\n";
    fout << "CP9 Kaku 187 88 19 60 33 3029\n";
    fout << "BUILDING TowerOfJustice 194\n";
    fout << "STRAW_HAT Luffy 94 61 32 13 78 342910586\n";
    fout << "STRAW_HAT Zoro 145 35 11 36 59 825491036\n";
    fout << "STRAW_HAT Chopper 121 92 31 53 44 471029385\n";
    fout << "STRAW_HAT Franky 173 50 50 42 70 205847193\n";
    fout << "STRAW_HAT Nami 114 23 15 45 47 915830247\n";
    fout << "CP9 Lucci 129 57 38 16 65 2847\n";
    fout << "BUILDING MainGate 136\n";
    fout << "CP9 Blueno 138 39 33 55 55 4192\n";
    fout << "CP9 Jabra 157 47 18 21 38 4930\n";
    fout << "CP9 Fukurou 149 53 41 22 68 1845\n";
    fout << "CP9 Kumadori 82 15 27 30 61 1956\n";
    fout << "CONTEXT 71 52 44 60 83 36\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 17 72 62 100 100 67");
    remove("test.txt");
}

TEST_CASE("test_custom_random_40")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 211\n";
    fout << "BUILDING BusterCallShip 139\n";
    fout << "CP9 Kalifa 178 26 12 60 78 738492015\n";
    fout << "STRAW_HAT Usopp 142 58 16 32 42 194850273\n";
    fout << "STRAW_HAT Sanji 88 44 11 25 63 820491385\n";
    fout << "BUILDING BridgeOfHesitation 147\n";
    fout << "CP9 Kaku 150 29 41 15 48 3925\n";
    fout << "BUILDING TowerOfJustice 239\n";
    fout << "STRAW_HAT Luffy 121 21 29 55 52 582910473\n";
    fout << "STRAW_HAT Zoro 175 37 33 52 69 295018473\n";
    fout << "STRAW_HAT Chopper 94 85 15 30 35 483920154\n";
    fout << "STRAW_HAT Franky 134 53 14 38 45 710492835\n";
    fout << "STRAW_HAT Nami 118 47 26 11 57 639205814\n";
    fout << "CP9 Lucci 193 91 17 48 31 2184\n";
    fout << "BUILDING MainGate 122\n";
    fout << "CP9 Blueno 156 33 49 46 66 4739\n";
    fout << "CP9 Jabra 106 64 22 43 53 3105\n";
    fout << "CP9 Fukurou 127 50 35 14 74 1958\n";
    fout << "CP9 Kumadori 121 50 26 11 57 2847\n";
    fout << "CONTEXT 76 33 94 51 62 48\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 38 61 33 100 79 27");
    remove("test.txt");
}
TEST_CASE("test_custom_random_41")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 118\n";
    fout << "CP9 Kalifa 142 58 16 32 42 104928475\n";
    fout << "STRAW_HAT Usopp 88 44 11 25 63 930582147\n";
    fout << "STRAW_HAT Sanji 139 73 38 17 40 384920157\n";
    fout << "BUILDING BridgeOfHesitation 239\n";
    fout << "CP9 Kaku 134 53 14 38 45 3194\n";
    fout << "BUILDING TowerOfJustice 121\n";
    fout << "STRAW_HAT Luffy 127 50 35 14 74 294850173\n";
    fout << "STRAW_HAT Zoro 193 91 17 48 31 602948153\n";
    fout << "STRAW_HAT Chopper 156 33 49 46 66 849302154\n";
    fout << "STRAW_HAT Franky 150 29 41 15 48 4920\n";
    fout << "STRAW_HAT Nami 121 21 29 55 52 2740\n";
    fout << "CP9 Lucci 175 37 33 52 69 1843\n";
    fout << "BUILDING MainGate 106\n";
    fout << "CP9 Blueno 94 85 15 30 35 3759\n";
    fout << "CP9 Jabra 211 17 29 55 52 4029\n";
    fout << "CP9 Kumadori 211 26 12 60 78 3594\n";
    fout << "CONTEXT 76 33 94 51 62 48\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 48 72 28 100 74 64");
    remove("test.txt");
}

TEST_CASE("test_custom_random_42")
{
    ofstream fout("test.txt");
    fout << "BUILDING BusterCallShip 179\n";
    fout << "CP9 Kalifa 127 50 35 14 74 539201847\n";
    fout << "STRAW_HAT Usopp 193 91 17 48 31 205847193\n";
    fout << "STRAW_HAT Sanji 156 33 49 46 66 915830247\n";
    fout << "BUILDING BridgeOfHesitation 147\n";
    fout << "CP9 Kaku 106 64 22 43 53 3029\n";
    fout << "BUILDING TowerOfJustice 239\n";
    fout << "STRAW_HAT Luffy 118 47 26 11 57 342910586\n";
    fout << "STRAW_HAT Zoro 178 26 12 60 78 825491036\n";
    fout << "STRAW_HAT Chopper 142 58 16 32 42 291503847\n";
    fout << "STRAW_HAT Franky 88 44 11 25 63 601928475\n";
    fout << "STRAW_HAT Nami 139 73 38 17 40 471029385\n";
    fout << "BUILDING MainGate 122\n";
    fout << "CP9 Blueno 121 21 29 55 52 4192\n";
    fout << "CP9 Jabra 175 37 33 52 69 4930\n";
    fout << "CP9 Fukurou 94 85 15 30 35 1845\n";
    fout << "CP9 Kumadori 134 53 14 38 45 1956\n";
    fout << "CONTEXT 62 48 76 33 94 51\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 69 58 100 100 80");
    remove("test.txt");
}

TEST_CASE("test_custom_random_43")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 136\n";
    fout << "BUILDING BusterCallShip 252\n";
    fout << "CP9 Kalifa 164 43 14 49 52 639205814\n";
    fout << "STRAW_HAT Usopp 108 76 46 27 76 295018473\n";
    fout << "BUILDING BridgeOfHesitation 122\n";
    fout << "CP9 Kaku 129 57 38 16 65 2184\n";
    fout << "BUILDING TowerOfJustice 194\n";
    fout << "STRAW_HAT Luffy 187 88 19 60 33 820491385\n";
    fout << "STRAW_HAT Zoro 94 61 32 13 78 738492015\n";
    fout << "STRAW_HAT Chopper 145 35 11 36 59 194850273\n";
    fout << "STRAW_HAT Franky 121 92 31 53 44 483920154\n";
    fout << "STRAW_HAT Nami 173 50 50 42 70 582910473\n";
    fout << "CP9 Lucci 114 23 15 45 47 3105\n";
    fout << "BUILDING MainGate 169\n";
    fout << "CP9 Blueno 149 53 41 22 68 4739\n";
    fout << "CP9 Jabra 82 15 27 30 61 1958\n";
    fout << "CP9 Kumadori 157 47 18 21 38 2847\n";
    fout << "CONTEXT 83 36 71 52 44 60\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 47 92 31 100 70 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_44")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 187\n";
    fout << "BUILDING BusterCallShip 104\n";
    fout << "CP9 Kalifa 113 27 50 36 66 294850173\n";
    fout << "STRAW_HAT Sanji 82 59 33 14 78 502914837\n";
    fout << "BUILDING BridgeOfHesitation 173\n";
    fout << "CP9 Kaku 155 46 22 43 49 4829\n";
    fout << "BUILDING TowerOfJustice 218\n";
    fout << "STRAW_HAT Luffy 176 34 45 19 55 930482516\n";
    fout << "STRAW_HAT Zoro 127 76 11 52 32 384920516\n";
    fout << "STRAW_HAT Chopper 191 50 29 26 73 184930275\n";
    fout << "STRAW_HAT Franky 138 43 38 60 60 620584913\n";
    fout << "STRAW_HAT Nami 109 82 14 31 44 472910583\n";
    fout << "CP9 Lucci 122 64 41 12 57 1930\n";
    fout << "BUILDING MainGate 233\n";
    fout << "CP9 Blueno 141 38 18 47 36 3752\n";
    fout << "CP9 Jabra 164 21 46 25 71 2749\n";
    fout << "CP9 Fukurou 98 55 34 33 53 3847\n";
    fout << "CP9 Kumadori 134 49 15 58 79 4829\n";
    fout << "CONTEXT 49 81 54 28 67 43\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 39 20 70 100 73 30");
    remove("test.txt");
}

TEST_CASE("test_custom_random_45")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 225\n";
    fout << "BUILDING BusterCallShip 163\n";
    fout << "CP9 Kalifa 152 44 19 60 53 930481275\n";
    fout << "STRAW_HAT Usopp 121 73 34 25 77 472910485\n";
    fout << "STRAW_HAT Sanji 194 36 46 41 39 104928375\n";
    fout << "BUILDING BridgeOfHesitation 249\n";
    fout << "CP9 Kaku 116 51 11 16 68 3847\n";
    fout << "BUILDING TowerOfJustice 134\n";
    fout << "STRAW_HAT Luffy 140 88 28 54 46 602941837\n";
    fout << "STRAW_HAT Zoro 171 19 40 32 62 829501472\n";
    fout << "STRAW_HAT Chopper 103 62 15 47 31 384029154\n";
    fout << "STRAW_HAT Franky 158 55 50 13 74 719483026\n";
    fout << "STRAW_HAT Nami 86 95 23 37 50 502948173\n";
    fout << "CP9 Lucci 133 30 33 58 42 2749\n";
    fout << "BUILDING MainGate 157\n";
    fout << "CP9 Blueno 177 47 14 21 65 4103\n";
    fout << "CP9 Jabra 125 58 27 49 57 1958\n";
    fout << "CP9 Kumadori 92 41 49 11 79 4830\n";
    fout << "CONTEXT 61 52 44 79 36 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 13 63 62 100 100 24");
    remove("test.txt");
}

TEST_CASE("test_custom_random_46")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 144\n";
    fout << "BUILDING BusterCallShip 237\n";
    fout << "CP9 Kalifa 94 58 26 33 45 401928473\n";
    fout << "STRAW_HAT Usopp 173 41 42 56 31 829501473\n";
    fout << "STRAW_HAT Sanji 111 96 15 18 73 602948371\n";
    fout << "BUILDING BridgeOfHesitation 116\n";
    fout << "CP9 Kaku 134 29 48 44 60 1958\n";
    fout << "BUILDING TowerOfJustice 211\n";
    fout << "STRAW_HAT Luffy 156 64 30 12 55 384029157\n";
    fout << "STRAW_HAT Zoro 99 78 19 39 67 104928374\n";
    fout << "STRAW_HAT Chopper 182 23 34 51 42 719483025\n";
    fout << "STRAW_HAT Franky 147 50 50 27 79 930481572\n";
    fout << "STRAW_HAT Nami 128 85 11 60 48 502941837\n";
    fout << "CP9 Blueno 106 47 37 49 38 3104\n";
    fout << "CP9 Jabra 142 53 14 22 66 2749\n";
    fout << "CP9 Fukurou 122 19 29 57 71 3840\n";
    fout << "CONTEXT 34 77 91 46 58 62\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 58 31 100 91 46 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_47")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 209\n";
    fout << "CP9 Kalifa 136 22 43 19 70 592014837\n";
    fout << "STRAW_HAT Usopp 105 85 16 44 38 384920157\n";
    fout << "STRAW_HAT Sanji 162 49 31 52 59 719482053\n";
    fout << "BUILDING BridgeOfHesitation 193\n";
    fout << "CP9 Kaku 157 37 14 60 51 4029\n";
    fout << "BUILDING TowerOfJustice 142\n";
    fout << "STRAW_HAT Luffy 114 93 49 28 42 294850173\n";
    fout << "STRAW_HAT Zoro 179 61 25 13 77 602948153\n";
    fout << "STRAW_HAT Chopper 138 34 50 36 65 849302154\n";
    fout << "STRAW_HAT Franky 83 76 11 57 33 104928475\n";
    fout << "STRAW_HAT Nami 191 18 28 41 54 930582147\n";
    fout << "CP9 Lucci 125 55 37 23 48 3194\n";
    fout << "BUILDING MainGate 248\n";
    fout << "CP9 Blueno 144 43 20 47 63 2740\n";
    fout << "CP9 Jabra 101 50 33 15 79 4920\n";
    fout << "CP9 Kumadori 150 31 46 32 56 3759\n";
    fout << "CONTEXT 55 63 32 84 47 91\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 57 73 100 100 48");
    remove("test.txt");
}

TEST_CASE("test_custom_random_48")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 168\n";
    fout << "BUILDING BusterCallShip 231\n";
    fout << "CP9 Kalifa 119 54 22 47 31 105938472\n";
    fout << "STRAW_HAT Usopp 142 77 36 12 55 930482516\n";
    fout << "STRAW_HAT Sanji 185 39 18 59 43 472910583\n";
    fout << "BUILDING BridgeOfHesitation 140\n";
    fout << "CP9 Kaku 113 25 45 31 67 2948\n";
    fout << "BUILDING TowerOfJustice 251\n";
    fout << "STRAW_HAT Luffy 81 94 13 26 79 384920516\n";
    fout << "STRAW_HAT Zoro 158 63 49 41 36 620584913\n";
    fout << "STRAW_HAT Chopper 197 19 27 53 50 184930275\n";
    fout << "STRAW_HAT Franky 126 82 11 16 62 502914837\n";
    fout << "STRAW_HAT Nami 104 46 34 38 74 719402853\n";
    fout << "CP9 Lucci 141 33 50 20 58 3752\n";
    fout << "BUILDING MainGate 177\n";
    fout << "CP9 Fukurou 152 28 14 18 52 3847\n";
    fout << "CP9 Kumadori 107 49 38 60 45 2749\n";
    fout << "CONTEXT 92 41 68 25 74 39\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 39 100 71 100 73 38");
    remove("test.txt");
}

TEST_CASE("test_custom_random_49")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 245\n";
    fout << "BUILDING BusterCallShip 153\n";
    fout << "CP9 Kalifa 82 61 38 14 59 738492015\n";
    fout << "STRAW_HAT Usopp 164 29 15 53 47 194850273\n";
    fout << "STRAW_HAT Sanji 105 88 43 21 70 820491385\n";
    fout << "BUILDING BridgeOfHesitation 182\n";
    fout << "CP9 Kaku 149 42 27 36 33 3925\n";
    fout << "BUILDING TowerOfJustice 119\n";
    fout << "STRAW_HAT Luffy 123 74 19 49 65 582910473\n";
    fout << "STRAW_HAT Zoro 187 35 31 16 52 295018473\n";
    fout << "STRAW_HAT Franky 199 15 11 27 76 710492835\n";
    fout << "STRAW_HAT Nami 136 92 25 58 41 639205814\n";
    fout << "CP9 Lucci 108 57 14 30 55 2184\n";
    fout << "BUILDING MainGate 206\n";
    fout << "CP9 Blueno 124 39 46 22 68 4739\n";
    fout << "CP9 Jabra 155 47 18 60 44 3105\n";
    fout << "CP9 Fukurou 91 23 32 45 61 1958\n";
    fout << "CONTEXT 43 85 19 64 32 55\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 34 71 90 100 77 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_50")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 112\n";
    fout << "BUILDING BusterCallShip 198\n";
    fout << "CP9 Kalifa 145 31 12 55 42 291503847\n";
    fout << "STRAW_HAT Usopp 88 52 41 29 63 601928475\n";
    fout << "STRAW_HAT Sanji 120 73 16 48 35 342910586\n";
    fout << "BUILDING BridgeOfHesitation 215\n";
    fout << "BUILDING TowerOfJustice 167\n";
    fout << "STRAW_HAT Luffy 193 26 24 38 51 825491036\n";
    fout << "STRAW_HAT Zoro 134 85 15 52 69 471029385\n";
    fout << "STRAW_HAT Chopper 156 44 38 17 40 915830247\n";
    fout << "STRAW_HAT Franky 115 91 22 30 57 205847193\n";
    fout << "STRAW_HAT Nami 178 37 49 43 31 539201847\n";
    fout << "CP9 Lucci 127 48 29 25 66 4192\n";
    fout << "BUILDING MainGate 139\n";
    fout << "CP9 Blueno 150 21 17 46 53 3029\n";
    fout << "CP9 Jabra 93 64 35 32 48 2847\n";
    fout << "CP9 Fukurou 139 50 11 14 78 4930\n";
    fout << "CONTEXT 76 29 55 41 63 87\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 64 86 39 100 94 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_51")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 221\n";
    fout << "CP9 Kalifa 115 53 24 39 67 295810473\n";
    fout << "STRAW_HAT Usopp 179 42 18 60 44 639205814\n";
    fout << "STRAW_HAT Sanji 138 23 32 45 61 194850273\n";
    fout << "BUILDING BridgeOfHesitation 194\n";
    fout << "CP9 Kaku 108 50 20 13 78 4739\n";
    fout << "BUILDING TowerOfJustice 125\n";
    fout << "STRAW_HAT Luffy 132 57 14 30 55 582910473\n";
    fout << "STRAW_HAT Zoro 155 39 46 22 68 295018473\n";
    fout << "STRAW_HAT Chopper 124 47 18 60 44 820491385\n";
    fout << "STRAW_HAT Franky 91 61 38 14 59 710492835\n";
    fout << "STRAW_HAT Nami 149 29 15 53 47 483920154\n";
    fout << "CP9 Lucci 164 88 43 21 70 3105\n";
    fout << "BUILDING MainGate 206\n";
    fout << "CP9 Blueno 157 35 31 16 52 1958\n";
    fout << "CP9 Jabra 119 53 50 42 38 2847\n";
    fout << "CP9 Kumadori 187 92 25 58 41 2184\n";
    fout << "CONTEXT 52 19 64 32 55 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 62 49 34 100 85 57");
    remove("test.txt");
}

TEST_CASE("test_custom_random_52")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 176\n";
    fout << "BUILDING BusterCallShip 238\n";
    fout << "STRAW_HAT Usopp 135 41 29 55 69 502914837\n";
    fout << "STRAW_HAT Sanji 152 28 14 18 52 930482516\n";
    fout << "BUILDING BridgeOfHesitation 113\n";
    fout << "CP9 Kaku 107 49 38 60 45 1930\n";
    fout << "BUILDING TowerOfJustice 219\n";
    fout << "STRAW_HAT Luffy 119 54 22 47 31 384920516\n";
    fout << "STRAW_HAT Zoro 142 77 36 12 55 184930275\n";
    fout << "STRAW_HAT Chopper 185 39 18 59 43 620584913\n";
    fout << "STRAW_HAT Franky 81 94 13 26 79 472910583\n";
    fout << "STRAW_HAT Nami 158 63 49 41 36 105938472\n";
    fout << "CP9 Lucci 197 19 27 53 50 3752\n";
    fout << "BUILDING MainGate 140\n";
    fout << "CP9 Blueno 126 82 11 16 62 4829\n";
    fout << "CP9 Jabra 104 46 34 38 74 2749\n";
    fout << "CP9 Kumadori 96 58 16 43 40 4829\n";
    fout << "CONTEXT 41 68 25 74 39 92\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 40 46 75 100 92 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_53")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 144\n";
    fout << "BUILDING BusterCallShip 191\n";
    fout << "CP9 Kalifa 125 55 37 23 48 294850173\n";
    fout << "STRAW_HAT Sanji 101 50 33 15 79 849302154\n";
    fout << "BUILDING BridgeOfHesitation 248\n";
    fout << "CP9 Kaku 119 27 18 53 45 104928475\n";
    fout << "BUILDING TowerOfJustice 157\n";
    fout << "STRAW_HAT Luffy 136 22 43 19 70 930582147\n";
    fout << "STRAW_HAT Zoro 105 85 16 44 38 384920157\n";
    fout << "STRAW_HAT Chopper 162 49 31 52 59 719482053\n";
    fout << "STRAW_HAT Franky 157 37 14 60 51 3194\n";
    fout << "STRAW_HAT Nami 114 93 49 28 42 2740\n";
    fout << "CP9 Lucci 179 61 25 13 77 4920\n";
    fout << "BUILDING MainGate 193\n";
    fout << "CP9 Blueno 138 34 50 36 65 1843\n";
    fout << "CP9 Fukurou 150 31 46 32 56 4029\n";
    fout << "CP9 Kumadori 209 18 28 41 54 2090\n";
    fout << "CONTEXT 63 32 84 47 91 55\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 55 37 100 100 78");
    remove("test.txt");
}

TEST_CASE("test_custom_random_54")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 189\n";
    fout << "BUILDING BusterCallShip 106\n";
    fout << "CP9 Kalifa 159 36 22 15 54 401928473\n";
    fout << "STRAW_HAT Usopp 106 47 37 49 38 829501473\n";
    fout << "STRAW_HAT Sanji 142 53 14 22 66 602948371\n";
    fout << "BUILDING BridgeOfHesitation 122\n";
    fout << "CP9 Kaku 122 19 29 57 71 1958\n";
    fout << "BUILDING TowerOfJustice 175\n";
    fout << "STRAW_HAT Luffy 94 58 26 33 45 384029157\n";
    fout << "STRAW_HAT Zoro 173 41 42 56 31 104928374\n";
    fout << "STRAW_HAT Chopper 111 96 15 18 73 719483025\n";
    fout << "STRAW_HAT Franky 134 29 48 44 60 930481572\n";
    fout << "STRAW_HAT Nami 156 64 30 12 55 502941837\n";
    fout << "CP9 Lucci 99 78 19 39 67 4829\n";
    fout << "BUILDING MainGate 116\n";
    fout << "CP9 Blueno 182 23 34 51 42 3104\n";
    fout << "CP9 Jabra 147 50 50 27 79 2749\n";
    fout << "CONTEXT 77 91 46 58 62 34\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 34 100 80 100 96 30");
    remove("test.txt");
}

TEST_CASE("test_custom_random_55")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 157\n";
    fout << "BUILDING BusterCallShip 177\n";
    fout << "CP9 Kalifa 133 30 33 58 42 930481275\n";
    fout << "STRAW_HAT Usopp 116 51 11 16 68 472910485\n";
    fout << "STRAW_HAT Sanji 125 58 27 49 57 104928375\n";
    fout << "BUILDING BridgeOfHesitation 149\n";
    fout << "CP9 Kaku 92 41 49 11 79 3847\n";
    fout << "BUILDING TowerOfJustice 249\n";
    fout << "STRAW_HAT Luffy 152 44 19 60 53 602941837\n";
    fout << "STRAW_HAT Zoro 121 73 34 25 77 829501472\n";
    fout << "STRAW_HAT Chopper 194 36 46 41 39 384029154\n";
    fout << "STRAW_HAT Nami 171 19 40 32 62 502948173\n";
    fout << "CP9 Lucci 103 62 15 47 31 2749\n";
    fout << "BUILDING MainGate 134\n";
    fout << "CP9 Jabra 86 95 23 37 50 1958\n";
    fout << "CP9 Fukurou 149 24 42 33 35 3194\n";
    fout << "CP9 Kumadori 225 47 14 21 65 4830\n";
    fout << "CONTEXT 52 44 79 36 83 61\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 14 43 44 100 100 70");
    remove("test.txt");
}

TEST_CASE("test_custom_random_56")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 233\n";
    fout << "BUILDING BusterCallShip 141\n";
    fout << "STRAW_HAT Usopp 155 46 22 43 49 719402853\n";
    fout << "STRAW_HAT Sanji 164 21 46 25 71 502914837\n";
    fout << "BUILDING BridgeOfHesitation 113\n";
    fout << "CP9 Kaku 98 55 34 33 53 4829\n";
    fout << "BUILDING TowerOfJustice 173\n";
    fout << "STRAW_HAT Luffy 113 27 50 36 66 930482516\n";
    fout << "STRAW_HAT Zoro 149 91 16 57 41 384920516\n";
    fout << "STRAW_HAT Chopper 82 59 33 14 78 184930275\n";
    fout << "STRAW_HAT Franky 176 34 45 19 55 620584913\n";
    fout << "STRAW_HAT Nami 127 76 11 52 32 472910583\n";
    fout << "CP9 Lucci 191 50 29 26 73 1930\n";
    fout << "BUILDING MainGate 218\n";
    fout << "CP9 Blueno 138 43 38 60 60 3752\n";
    fout << "CP9 Jabra 109 82 14 31 44 2749\n";
    fout << "CP9 Fukurou 134 49 15 58 79 3847\n";
    fout << "CP9 Kumadori 187 38 18 47 36 4829\n";
    fout << "CONTEXT 81 54 28 67 43 49\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "BUSTER_CALL 44 76 74 100 85 0");
    remove("test.txt");
}

TEST_CASE("test_custom_random_57")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 169\n";
    fout << "BUILDING BusterCallShip 149\n";
    fout << "CP9 Kalifa 114 23 15 45 47 639205814\n";
    fout << "STRAW_HAT Usopp 129 57 38 16 65 295018473\n";
    fout << "STRAW_HAT Sanji 82 15 27 30 61 710492835\n";
    fout << "BUILDING BridgeOfHesitation 129\n";
    fout << "CP9 Kaku 138 39 33 55 55 2184\n";
    fout << "BUILDING TowerOfJustice 122\n";
    fout << "STRAW_HAT Luffy 164 43 14 49 52 820491385\n";
    fout << "STRAW_HAT Zoro 108 76 46 27 76 738492015\n";
    fout << "STRAW_HAT Chopper 153 29 25 58 41 194850273\n";
    fout << "STRAW_HAT Franky 187 88 19 60 33 483920154\n";
    fout << "STRAW_HAT Nami 94 61 32 13 78 582910473\n";
    fout << "CP9 Lucci 145 35 11 36 59 3105\n";
    fout << "BUILDING MainGate 194\n";
    fout << "CP9 Blueno 121 92 31 53 44 4739\n";
    fout << "CP9 Jabra 173 50 50 42 70 1958\n";
    fout << "CONTEXT 36 71 52 44 60 83\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN_BY_DEFEAT_CP9 42 68 75 100 77 21");
    remove("test.txt");
}

TEST_CASE("test_custom_random_58")
{
    ofstream fout("test.txt");
    fout << "BUILDING BusterCallShip 121\n";
    fout << "CP9 Kalifa 150 29 41 15 48 539201847\n";
    fout << "STRAW_HAT Usopp 106 64 22 43 53 205847193\n";
    fout << "STRAW_HAT Sanji 175 37 33 52 69 915830247\n";
    fout << "BUILDING BridgeOfHesitation 106\n";
    fout << "CP9 Kaku 94 85 15 30 35 3029\n";
    fout << "BUILDING TowerOfJustice 147\n";
    fout << "STRAW_HAT Luffy 127 50 35 14 74 342910586\n";
    fout << "STRAW_HAT Zoro 193 91 17 48 31 825491036\n";
    fout << "STRAW_HAT Chopper 156 33 49 46 66 291503847\n";
    fout << "STRAW_HAT Franky 118 47 26 11 57 601928475\n";
    fout << "STRAW_HAT Nami 178 26 12 60 78 471029385\n";
    fout << "CP9 Lucci 142 58 16 32 42 2847\n";
    fout << "BUILDING MainGate 239\n";
    fout << "CP9 Blueno 88 44 11 25 63 4192\n";
    fout << "CP9 Jabra 139 73 38 17 40 4930\n";
    fout << "CP9 Fukurou 134 53 14 38 45 1845\n";
    fout << "CP9 Kumadori 211 17 29 55 52 1956\n";
    fout << "CONTEXT 48 76 33 94 51 62\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 1 58 76 33 100 50");
    remove("test.txt");
}

TEST_CASE("test_custom_random_59")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 142\n";
    fout << "BUILDING BusterCallShip 105\n";
    fout << "CP9 Kalifa 136 49 31 52 59 620584719\n";
    fout << "STRAW_HAT Sanji 114 93 49 28 42 845291307\n";
    fout << "BUILDING BridgeOfHesitation 157\n";
    fout << "CP9 Kaku 105 85 16 44 38 2748\n";
    fout << "BUILDING TowerOfJustice 111\n";
    fout << "STRAW_HAT Luffy 144 34 46 32 56 719402563\n";
    fout << "STRAW_HAT Zoro 119 76 11 57 33 502419385\n";
    fout << "STRAW_HAT Chopper 150 18 28 41 54 384729104\n";
    fout << "STRAW_HAT Franky 125 31 46 17 55 194850372\n";
    fout << "STRAW_HAT Nami 162 22 43 19 70 519300000\n";
    fout << "CP9 Lucci 111 61 25 13 77 1952\n";
    fout << "BUILDING MainGate 114\n";
    fout << "CP9 Blueno 138 43 20 47 63 4310\n";
    fout << "CP9 Jabra 83 50 33 15 79 3824\n";
    fout << "CP9 Fukurou 191 27 18 53 45 2740\n";
    fout << "CP9 Kumadori 158 55 37 23 48 3594\n";
    fout << "CONTEXT 44 83 62 38 74 51\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 26 3 70 100 38 50");
    remove("test.txt");
}

TEST_CASE("test_custom_random_60")
{
    ofstream fout("test.txt");
    fout << "BUILDING Courthouse 118\n";
    fout << "BUILDING BusterCallShip 178\n";
    fout << "CP9 Kalifa 142 58 16 32 42 104928475\n";
    fout << "STRAW_HAT Usopp 88 44 11 25 63 930582147\n";
    fout << "STRAW_HAT Sanji 139 73 38 17 40 384920157\n";
    fout << "BUILDING BridgeOfHesitation 239\n";
    fout << "CP9 Kaku 134 53 14 38 45 3194\n";
    fout << "BUILDING TowerOfJustice 121\n";
    fout << "STRAW_HAT Luffy 127 50 35 14 74 294850173\n";
    fout << "STRAW_HAT Zoro 193 91 17 48 31 602948153\n";
    fout << "STRAW_HAT Chopper 156 33 49 46 66 849302154\n";
    fout << "STRAW_HAT Franky 150 29 41 15 48 4920\n";
    fout << "STRAW_HAT Nami 121 21 29 55 52 2740\n";
    fout << "CP9 Lucci 175 37 33 52 69 1843\n";
    fout << "BUILDING MainGate 106\n";
    fout << "CP9 Blueno 94 85 15 30 35 3759\n";
    fout << "CP9 Kumadori 211 26 12 60 78 3594\n";
    fout << "CONTEXT 76 33 94 51 62 48\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "CP9_WIN 47 67 28 100 74 17");
    remove("test.txt");
}
TEST_CASE("test_custom_random_61")
{
    ofstream fout("test.txt");
fout << "STRAW_HAT Luffy 142 17 25 29 34 905011535\n";
fout << "CP9 Blueno 124 27 31 22 30 3952\n";
fout << "BUILDING BridgeOfHesitation 157\n";
fout << "CONTEXT 35 74 48 42 16 56\n";
fout << "BUILDING Courthouse 106\n";
fout << "CP9 Fukurou 97 52 25 11 80 3351\n";
fout << "BUILDING MainGate 176\n";
fout << "CP9 Kumadori 143 41 10 19 73 3088\n";
fout << "STRAW_HAT Franky 162 46 14 42 47 685711256\n";
fout << "CP9 Kalifa 157 31 18 59 36 4340\n";
fout << "BUILDING TowerOfJustice 138\n";
fout << "STRAW_HAT Usopp 144 34 40 52 74 744841931\n";
fout << "CP9 Lucci 105 40 24 29 32 4421\n";
fout << "BUILDING BusterCallShip 114\n";
fout << "STRAW_HAT Chopper 151 80 10 53 75 803215197\n";
fout << "STRAW_HAT Zoro 165 50 22 30 53 944132744\n";
fout << "STRAW_HAT Nami 157 55 31 57 32 929344951\n";
fout << "CP9 Jabra 146 55 21 19 31 3213\n";
fout << "STRAW_HAT Sanji 156 41 10 39 44 852374889\n";
fout << "CP9 Kaku 143 50 24 30 30 4338\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "STRAW_HAT_WIN 17 57 75 100 100 0");
    remove("test.txt");
}
TEST_CASE("test_custom_random_62")
{
    ofstream fout("test.txt");
fout << "BUILDING Courthouse 137\n";
fout << "BUILDING BridgeOfHesitation 189\n";
fout << "CONTEXT 94 61 23 26 96 37\n";
fout << "STRAW_HAT Chopper 118 29 37 57 60 845049045\n";
fout << "BUILDING TowerOfJustice 193\n";
fout << "CP9 Lucci 148 53 10 48 34 3398\n";
fout << "BUILDING MainGate 135\n";
fout << "STRAW_HAT Usopp 77 37 8 21 37 292914882\n";
fout << "CP9 Kumadori 103 34 27 33 69 2524\n";
fout << "STRAW_HAT Nami 61 67 28 19 39 321096465\n";
fout << "STRAW_HAT Franky 188 23 26 13 49 166984142\n";
fout << "BUILDING BusterCallShip 162\n";
fout << "STRAW_HAT Sanji 198 66 11 15 58 489731167\n";
fout << "CP9 Fukurou 153 40 32 50 71 3347\n";
fout << "STRAW_HAT Luffy 116 41 7 27 38 137641218\n";
fout << "CP9 Jabra 121 41 13 20 40 3001\n";
fout << "CP9 Kaku 92 50 27 57 73 3425\n";
fout << "CP9 Kalifa 151 31 28 15 50 4382\n";
fout << "CP9 Blueno 152 41 24 25 43 4281\n";
fout << "STRAW_HAT Zoro 108 56 24 46 68 807658344\n";
    fout.close();

    EniesLobbyBattle battle("test.txt");
    battle.runBattle();
    CHECK(battle.getResult() == "TIME_OUT 37 94 71 100 59 60");
    remove("test.txt");
}