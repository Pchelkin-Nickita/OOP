#include "../GameState.h"

std::string GameState::getGameMap() const {
    return player->field.getFieldMap() + player->manager.getShipsMap() + opp->field.getFieldMap() + opp->manager.getShipsMap();
}

GameState::GameState(Player* player, Player* opp) : player(player), opp(opp) {}

void GameState::saveGame() {
    std::ofstream save;
    save.open("save.txt");
    if (save.is_open())
    {
        save << getGameMap();
    }
    save.close();
    std::cout << "Game has been saved!\n";

}

void GameState::loadGame() {
    std::string info;
    std::string line;
    std::ifstream load("save.txt");
    if (load.is_open()) {
        while (std::getline(load, line))
            info += line + '\n';

    }
    load.close();
    parseInfo(info);
    std::cout << "Game was loaded!\n";
}

void GameState::parseInfo(const std::string& info) {
    std::istringstream stream(info);

    player->field = buildBattlefield(stream);
    player->manager = buildShipManager(stream, player->field);

    opp->field = buildBattlefield(stream);
    opp->manager = buildShipManager(stream, opp->field);
}

Battlefield GameState::buildBattlefield(std::istringstream& stream)
{
    std::string line;
    std::getline(stream, line);
    int length = std::stoi(line);

    std::getline(stream, line);
    int width = std::stoi(line);

    std::getline(stream, line);
    bool is_visible = std::stoi(line) == 1 ? true : false;

    std::vector<std::vector<bool>> test_field(length, std::vector<bool>(width));
    for (int i = 0; i < length; i++)
        for (int j = 0; j < width; j++) {
            std::getline(stream, line);
            test_field[i][j] = std::stoi(line) == 1 ? true : false;
        }
    Battlefield field = Battlefield(length, width, test_field, is_visible);
    return field;
}

ShipManager GameState::buildShipManager(std::istringstream& stream, Battlefield& field)
{
    std::map<unsigned, std::vector<std::pair<Ship, std::pair<std::pair<int, int>, Orientation>>>> ships;
    std::string line;
    for (int i = 1; i <= 4; i++) {
        std::getline(stream, line);
        int n = std::stoi(line);
        for (int j = 0; j < n; j++) {
            std::vector<int> map_segments(i);
            std::getline(stream, line);
            int x = std::stoi(line);
            std::getline(stream, line);
            int y = std::stoi(line);
            std::getline(stream, line);
            Orientation orient = std::stoi(line) == 0 ? VERTICAL : HORIZONTAL;
            for (int k = 0; k < i; k++) {
                std::getline(stream, line);
                map_segments[k] = std::stoi(line);
            }
            ships[i].push_back({ Ship(map_segments), {{x, y}, orient} });
        }
    }
    ShipManager manager = ShipManager(ships, field);
    return manager;
}

std::ostream& operator<<(std::ostream& os, const GameState& game_state) {
    os << game_state.getGameMap();
    return os;
}
std::istream& operator>>(std::istream& is, GameState& gState) {
    std::ostringstream buffer;
    std::string line;
    while (std::getline(is, line))
    {
        buffer << line << "\n";
    }
    gState.parseInfo(buffer.str());
    return is;
}
