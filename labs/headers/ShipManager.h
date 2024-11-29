#pragma once
#include <vector>
#include <map>
#include "Battlefield.h"
#include "Ship.h"

class ShipManager {
    friend class Shelling;
private:
    std::map<unsigned, std::vector<std::pair<Ship, std::pair<std::pair<int, int>, Orientation>>>> inactive_ships;
    std::map<unsigned, std::vector<std::pair<Ship, std::pair<std::pair<int, int>, Orientation>>>> active_ships;
public:
    ShipManager() = default;
    ShipManager(std::map<unsigned, unsigned> number_of_ships);
    ShipManager(std::map<unsigned, std::vector<std::pair<Ship, std::pair<std::pair<int, int>, Orientation>>>> ships, Battlefield& field);

    bool placeShip(Battlefield& field, int length, int x, int y, Orientation orient);

    bool endOfSetting();

    void settingInfo();

    void Info();

    bool updateInfo();

    bool gameOver();

    void reset();

    std::string getShipsMap();
};