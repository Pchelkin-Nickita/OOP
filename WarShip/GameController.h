#pragma once

#include "InputVar.h"

class GameController {
	Game& game;	
public:
	GameController(Game& game);

	void acceptCommand(ICommand* command);
};