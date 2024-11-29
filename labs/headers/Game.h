#pragma once

#include "AbilityManager.h"
#include "GameState.h"


struct GameSettings {
	const int length = 9;
	const int width = 9;
	std::map<unsigned, unsigned> number_of_ships = { {1, 4}, {2, 3}, {3, 2}, {4, 1} };
};

class Game {
private:
	std::map<unsigned, unsigned> number_of_ships;
	Player player, opp;
	AbilityManager ability_manager;
	GameState state = GameState(&player, &opp);
	bool is_running = false;
	void placeShips();
	void spawnOpp();
	void oppsTurn();
	void gameOver();
public:
	Game(GameSettings& settings);

	void printMessage(std::string message);

	void printInfo();

	void printSettingInfo();

	void startGame();

	void checkAbilities();

	void printInfoAbilities();

	void useAbility();

	void attack(std::pair<int, int> coords);

	void printMyField();
	
	void printOppsField();

	bool isRunning();

	void saveGame();

	void loadGame();
};