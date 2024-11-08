#pragma once
#include <vector>
#include <map>
#include "Battlefield.h"
#include "Ship.h"

class ShipManager {
    friend class Shelling;
private:
    std::map<unsigned, std::vector<Ship>> inactive_ships;
    std::map<unsigned, std::vector<Ship>> active_ships;
public:
    ShipManager(int* number_of_ships);

    void set_ship(Battlefield& field, int length, int x, int y, Orientation orient);

    bool end_of_setting();

    void setting_info();

    bool updateInfo();

    bool game_over();
};