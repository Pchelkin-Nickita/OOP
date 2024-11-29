#pragma once

#include "CLI.h"


class GameController {
	Game& game;
	CLIInput CLI;
	bool ability_is_used = false;
public:
	GameController(Game& game);

	void startGame();

	void acceptCommand(ICommand* command);
};