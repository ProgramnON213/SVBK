#include "eniesLobby.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

// Cấu trúc bản sao vùng nhớ để bẻ khóa thuộc tính private của EniesLobbyBattle
struct EniesLobbyBattleBypass {
    Character** strawHats;
    int strawHatCount;
    Character** cp9Agents;
    int cp9Count;
    Building** buildings;
    int buildingCount;
    TurnNode* turnOrder;
    BattleContext context;
    int maxTurns;
};

// Hàm bổ trợ in trạng thái BattleContext của từng Turn
void printContext(const BattleContext& ctx) {
    cout << "   ✨ [BATTLE CONTEXT] TurnCount=" << ctx.turnCount 
         << " | Morale=" << ctx.morale 
         << " | Alarm=" << ctx.alarmLevel 
         << " | Rescue=" << ctx.rescueProgress 
         << " | Escape=" << ctx.escapeProgress 
         << " | BusterCall=" << ctx.busterCallTimer << endl;
}

// Hàm bổ trợ in thông tin chi tiết của một Character (StrawHat hoặc CP9)
void printCharacterInfo(const string& prefix, Character* c) {
    if (c == nullptr) return;
    cout << prefix << c->getName() << " -> HP=" << c->getHP() << "/" << c->getMaxHP() 
         << " | Def=" << c->getDef() << " | Speed=" << c->getSpeed() 
         << " | Energy=" << c->getEnergy() << " | Alive=" << (c->isAlive() ? "TRUE" : "DEAD 💀") << endl;
}

// Hàm bổ trợ in thông tin chi tiết của một Building
void printBuildingInfo(const string& prefix, Building* b) {
    if (b == nullptr) return;
    cout << prefix << b->getName() << " -> HP=" << b->getHP() << "/" << b->getMaxHP() 
         << " | Destroyed=" << (b->isDestroyed() ? "TRUE 💥" : "FALSE") << endl;
}
int main() {
    cout << "=======================================================" << endl;
    cout << "🔥 SIMULATION DEBUG TỪNG TURN GỒM ACTOR & TARGET CỦA BẢO 🔥" << endl;
    cout << "=======================================================" << endl;

    // 1. Khởi tạo trận đấu đọc từ file Kiemtra.txt của m
    EniesLobbyBattle battle("Kiemtra.txt");

    // 2. Ép kiểu con trỏ để bẻ khóa thọc vào vùng private
    EniesLobbyBattleBypass* bypass = reinterpret_cast<EniesLobbyBattleBypass*>(&battle);

    // Kích hoạt build lượt đi ban đầu
    battle.buildTurnOrder();

    cout << "Trạng thái khởi tạo ban đầu trận đấu:" << endl;
    printContext(bypass->context);
    cout << "-------------------------------------------------------" << endl;

    // 3. Vòng lặp giả lập mô phỏng
    while (!bypass->context.battleEnded && bypass->context.turnCount < bypass->maxTurns) {
        if (bypass->turnOrder == nullptr) {
            cout << "[ERROR] Vòng tròn lượt đi turnOrder bị rỗng m ơi!" << endl;
            break;
        }

        Character* actor = bypass->turnOrder->data;

        if (actor != nullptr && actor->isAlive()) {
            cout << "👉 [TURN " << bypass->context.turnCount << "] Đến lượt: " << actor->getName() 
                 << " (" << (actor->isStrawHat() ? "StrawHat" : "CP9") << ")" << endl;
            printCharacterInfo("   [Actor TRƯỚC lượt] ", actor);

            // Dò tìm trước xem lượt này Actor sẽ nhắm vào Target nào
            Building* buiTarget = nullptr;
            Character* charTarget = nullptr;

            if (actor->isStrawHat()) {
                Building* mainGate = battle.findBuildingWithName("MainGate");
                Building* courtHouse = battle.findBuildingWithName("Courthouse");
                Building* towerOfJustice = battle.findBuildingWithName("TowerOfJustice");
                Building* bridgeOfHesitation = battle.findBuildingWithName("BridgeOfHesitation");
                Building* busterCallShip = battle.findBuildingWithName("BusterCallShip");

                if (actor->getName() == "Chopper" && actor->getEnergy() >= 15) {
                    int leastHP = INT_MAX;
                    for (int i = 0; i < bypass->strawHatCount; i++) {
                        if (bypass->strawHats[i] != nullptr && bypass->strawHats[i]->isAlive()) {
                            if (bypass->strawHats[i]->getHP() < leastHP) {
                                leastHP = bypass->strawHats[i]->getHP();
                                charTarget = bypass->strawHats[i];
                            }
                        }
                    }
                }
                else if (!bypass->context.mainGateDestroyed) buiTarget = mainGate;
                else if (bypass->context.alarmLevel >= 50 && courtHouse != nullptr && !courtHouse->isDestroyed()) buiTarget = courtHouse;
                else if (bypass->context.busterCallTimer <= 5 && busterCallShip != nullptr && !busterCallShip->isDestroyed()) buiTarget = busterCallShip;
                else if (!bypass->context.robinRescued) {
                    for (int i = 0; i < bypass->cp9Count; i++) {
                        if (bypass->cp9Agents[i] != nullptr && bypass->cp9Agents[i]->isAlive()) {
                            charTarget = bypass->cp9Agents[i];
                            break;
                        }
                    }
                }
                else if (bridgeOfHesitation != nullptr && !bridgeOfHesitation->isDestroyed()) buiTarget = bridgeOfHesitation;
                else {
                    for (int i = 0; i < bypass->cp9Count; i++) {
                        if (bypass->cp9Agents[i] != nullptr && bypass->cp9Agents[i]->isAlive()) {
                            charTarget = bypass->cp9Agents[i];
                            break;
                        }
                    }
                }
            } else {
                for (int i = 0; i < bypass->strawHatCount; i++) {
                    if (bypass->strawHats[i] != nullptr && bypass->strawHats[i]->isAlive()) {
                        // 🔥 ĐÃ FIX: Đổi từ target sang charTarget chuẩn chỉ cho con vợ nhen!
                        charTarget = bypass->strawHats[i]; 
                        break;
                    }
                }
            }

            // In trạng thái của Target TRƯỚC KHI BỊ ĐẤM
            if (buiTarget != nullptr) {
                printBuildingInfo("   ⚔️  Nhắm vào CÔNG TRÌNH (TRƯỚC đấm): ", buiTarget);
            } else if (charTarget != nullptr) {
                printCharacterInfo("   ⚔️  Nhắm vào NHÂN VẬT (TRƯỚC đấm): ", charTarget);
            } else {
                cout << "   💤 Không có mục tiêu hợp lệ để đấm!" << endl;
            }

            // Gọi hàm xử lý lượt đi gốc của m
            battle.processTurn(actor);

            // Gọi hàm kết thúc lượt xử lý hiệu ứng của m
            actor->endTurn(bypass->context);

            // In trạng thái của Actor & Target SAU KHI ĐẤM XONG
            printCharacterInfo("   [Actor SAU lượt  ] ", actor);
            if (buiTarget != nullptr) {
                printBuildingInfo("   💥 Trạng thái CÔNG TRÌNH (SAU đấm ): ", buiTarget);
            } else if (charTarget != nullptr) {
                printCharacterInfo("   💥 Trạng thái NHÂN VẬT (SAU đấm ): ", charTarget);
            }
        } else if (actor != nullptr) {
            cout << "💀 [TURN " << bypass->context.turnCount << "] Thằng " << actor->getName() << " đã chết ngắc, skip lượt!" << endl;
        }

        // Đẩy vòng lượt tiếp theo
        bypass->turnOrder = bypass->turnOrder->next;

        // Quét hiệu ứng công trình cuối lượt
        battle.processBuildings();

        // Tăng TurnCount toàn cục
        bypass->context.nextTurn();

        // Check xem có ai chết sạch hay nổ đảo chưa
        battle.checkEndCondition();

        // Chốt sổ in Battle Context
        printContext(bypass->context);
        cout << "-------------------------------------------------------" << endl;
    }

    cout << "=======================================================" << endl;
    cout << "🏁 KẾT QUẢ CUỐI CÙNG TRÊN MÁY BẢO:" << endl;
    cout << "   👉 " << battle.getResult() << endl;
    cout << "=======================================================" << endl;

    return 0;
}