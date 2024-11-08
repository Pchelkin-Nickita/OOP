#pragma once

#include <iostream>
#include <queue>
#include <random>
#include <vector>

#include "enums.h"
#include "Args.h"


class IAbility {
public:
    virtual void useAbility() = 0;
    virtual ~IAbility() = default;
};


class DoubleDamage : public IAbility {
private:
    Battlefield* field;
public:
    DoubleDamage(DoubleDamageArgs& args) :field(args.field){}
    void useAbility() override {
        field->setDoubleDamage();
    }
};
class Scanner : public IAbility {
private:
    std::pair<int, int> coords;
    Battlefield* field;
public:
    Scanner(ScannerArgs& args) :coords(args.coords), field(args.field) {}
    void useAbility() override{
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (field->getState(coords.first + i, coords.second + j) == CellStatus::SHIP) {
                    std::cout << "Ship is on the area!!\n";
                    return;
                }
        std::cout << "There is NO ship on the area!!\n";
    }
};

class Shelling : public IAbility {
private:
    ShipManager* manager;
public:
    Shelling(ShellingArgs& args) :manager(args.manager) {}
    void useAbility() override {
        std::vector<Ship*> ships_to_attack;
        for(int i = 1; i <= 4; i++)
            for (int j = 0; j < manager->active_ships[i].size(); j++)
                ships_to_attack.push_back(&manager->active_ships[i][j]);
        Ship* ship_to_attack = ships_to_attack[rand() % ships_to_attack.size()];
        std::vector<Ship::Segment*> segments_to_attack;
        for (int i = 0; i < ship_to_attack->size(); i++)
            if (ship_to_attack->getSegment(i)->getStatus() != SegmentStatus::DESTROYED)
                segments_to_attack.push_back(ship_to_attack->getSegment(i));
        segments_to_attack[rand() % segments_to_attack.size()]->takeDamage();
    }
};