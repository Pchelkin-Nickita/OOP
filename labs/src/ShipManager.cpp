#include "ShipManager.h"
#include <iostream>

ShipManager::ShipManager(std::map<unsigned, unsigned> number_of_ships) {
    for (auto& item : number_of_ships) {
        for (int j = 0; j < item.second; j++) {
            std::pair<Ship, std::pair<std::pair<int, int>, Orientation>> ship = { Ship(item.first), {{1, 1}, HORIZONTAL} };
            inactive_ships[item.first].push_back(ship);
        }
    }
}

ShipManager::ShipManager(std::map<unsigned, std::vector<std::pair<Ship, std::pair<std::pair<int, int>, Orientation>>>> ships, Battlefield& field) {
    for (auto& item : ships) {
        for (int j = 0; j < item.second.size(); j++) {
            inactive_ships[item.first].push_back(item.second[j]);
            placeShip(field, item.first, item.second[j].second.first.first, item.second[j].second.first.second, item.second[j].second.second);
            updateInfo();
        }
    }
}

bool ShipManager::placeShip(Battlefield& field, int length, int x, int y, Orientation orient) {
    if (length < 1 and length > 4) {
        std::cout << "Wrong length for the ship!\n";
        return false;
    }
    if (inactive_ships[length].size() == 0) {
        std::cout << "There is no more ships of this length!\n";
        return false;
    }
    try {
        if (field.placeShip(inactive_ships[length].back().first, x, y, orient)) {
            active_ships[length].push_back(std::move(inactive_ships[length].back()));
            active_ships[length].back().second = { {x, y}, orient};
            inactive_ships[length].pop_back();
            return true;
        }
        else {
            throw std::logic_error("Can't place ship here!!");
        }
    }
    catch (std::exception& e) {
        std::cout << "\n\t" << e.what() << "\n";
        return false;
    }
}

bool ShipManager::endOfSetting() {
    for (auto& ship : inactive_ships)
        if (ship.second.size() != 0)
            return false;
    return true;
}

void ShipManager::settingInfo() {
    for (int i = 1; i <= 4; i++)
        std::cout << i << "-decker ships: " << inactive_ships[i].size() << std::endl;
}

void ShipManager::Info() {
    for (int i = 1; i <= 4; i++)
        std::cout << i << "-decker ships: " << active_ships[i].size() << std::endl;
}

bool ShipManager::updateInfo() {
    for (int i = 1; i <= 4; i++){
        for (int j = 0; j < active_ships[i].size(); j++)
            if (active_ships[i].at(j).first.isDestroyed()) {
                inactive_ships[i].push_back(std::move(active_ships[i].at(j)));
                active_ships[i].erase(active_ships[i].begin() + j);
                return true;
            }
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

void ShipManager::reset() {
    for (int i = 1; i <= 4; i++)
        for (int j = 0; j < inactive_ships[i].size(); j++) {
            inactive_ships[i][j].first.repair();
        }
}

std::string ShipManager::getShipsMap() {
    std::string map = "";
    for (int j = 1; j <= 4; j++) {
        map += std::to_string(inactive_ships[j].size() + active_ships[j].size()) + "\n";
        for (int i = 0; i < inactive_ships[j].size(); i++) {
            std::string map_info = inactive_ships[j][i].second.second == VERTICAL ? "0" : "1";
            map += std::to_string(inactive_ships[j][i].second.first.first) + "\n" + std::to_string(inactive_ships[j][i].second.first.second) + "\n" + map_info + "\n" + inactive_ships[j][i].first.getShipMap();
        }
        for (int i = 0; i < active_ships[j].size(); i++) {
            std::string map_info = active_ships[j][i].second.second == VERTICAL ? "0" : "1";
            map += std::to_string(active_ships[j][i].second.first.first) + "\n" + std::to_string(active_ships[j][i].second.first.second) + "\n" + map_info + "\n" + active_ships[j][i].first.getShipMap();
        }
    }
    return map;
}

