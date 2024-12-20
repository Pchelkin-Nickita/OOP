#pragma once

#include "DrawField.h"


class GameVisualizer{
	Game& game;
public:
	GameVisualizer(Game& game) : game(game) {}

	void acceptCommand(ICommand* command) {
		if (command != nullptr)
			command->execute(game);
	}
};