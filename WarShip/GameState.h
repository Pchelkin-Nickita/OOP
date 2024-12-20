#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "ShipManager.h"

struct Player {
    Battlefield field;
    ShipManager manager;
};

class GameState
{
private:
    Player* player;
    Player* opp;
    std::string getGameMap() const;
public:
    GameState(Player* player, Player* opp);

    void saveGame();

    void loadGame();
    
    void parseInfo(const std::string& info);

    Battlefield buildBattlefield(std::istringstream& stream);

    ShipManager buildShipManager(std::istringstream& stream, Battlefield& field);

    friend std::ostream& operator<<(std::ostream& os, const GameState& game_state);
    friend std::istream& operator>>(std::istream& is, GameState& gState);
};
