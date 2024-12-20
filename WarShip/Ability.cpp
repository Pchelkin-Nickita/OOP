#include "Ability.h"



DoubleDamage::DoubleDamage(DoubleDamageArgs& args) :field(args.field) {}
void DoubleDamage::useAbility() {
    field->setDoubleDamage();
}


Scanner::Scanner(ScannerArgs& args) :coords(args.coords), field(args.field) {}
void Scanner::useAbility() {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (field->getCellState(coords.first + i, coords.second + j) == CellStatus::SHIP) {
                std::cout << "Ship is on the area!!\n";
                return;
            }
    std::cout << "There is NO ship on the area!!\n";
}


Shelling::Shelling(ShellingArgs& args) :manager(args.manager) {}
void Shelling::useAbility() {
    std::vector<Ship*> ships_to_attack;
    for (int i = 1; i <= 4; i++)
        for (int j = 0; j < manager->active_ships[i].size(); j++)
            ships_to_attack.push_back(&manager->active_ships[i][j].first);
    Ship* ship_to_attack = ships_to_attack[rand() % ships_to_attack.size()];
    std::vector<Ship::Segment*> segments_to_attack;
    for (int i = 0; i < ship_to_attack->size(); i++)
        if (ship_to_attack->getSegment(i)->getStatus() != SegmentStatus::DESTROYED)
            segments_to_attack.push_back(ship_to_attack->getSegment(i));
    segments_to_attack[rand() % segments_to_attack.size()]->takeDamage();
}