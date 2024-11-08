#include "../headers/ShipManager.h"
#include <iostream>

ShipManager::ShipManager(int* number_of_ships) {
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < number_of_ships[i-1]; j++) {
            inactive_ships[i].push_back(Ship(i));
        }
    }
}

void ShipManager::setShip(Battlefield& field, int length, int x, int y, Orientation orient) {
    if (length < 1 and length > 4) {
        std::cout << "Wrong length for the ship!\n";
        return;
    }
    if (inactive_ships[length].size() == 0) {
        std::cout << "There is no more ships of this length!\n";
        return;
    }
    if (field.setShip(inactive_ships[length].back(), x, y, orient)) {
        active_ships[length].push_back(std::move(inactive_ships[length].back()));
        inactive_ships[length].pop_back();
    }
    else {
        throw std::length_error("You can't place ship here!\n");
    }
}

bool ShipManager::endOfSetting() {
    for (int i = 1; i <= 4; i++)
        if (inactive_ships[i].size() != 0)
            return false;
    return true;
}

void ShipManager::settingInfo() {
    for (int i = 1; i <= 4; i++)
        std::cout << i << ": " << inactive_ships[i].size() << std::endl;
}

bool ShipManager::updateInfo() {
    for (int i = 1; i <= 4; i++)
        for (int j = 0; j < active_ships[i].size(); j++)
            if (active_ships[i].at(j).isDestroyed()) {
                inactive_ships[i].push_back(std::move(active_ships[i].at(j)));
                active_ships[i].erase(active_ships[i].begin() + j);
                return true;
            }
    return false;
}

bool ShipManager::gameOver() {
    updateInfo();
    for (int i = 1; i <= 4; i++)
        if (active_ships[i].size() != 0)
            return false;
    return true;
}
