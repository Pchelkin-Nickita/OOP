#pragma once

#include "GameController.h"
#include "GameVisualizer.h"


template <class Input>
class GameManager {
private:
	Game& game;
	Input input;
	InterfaceSymbols& registers;
	GameController* controller;
	GameVisualizer* visualizer;
	bool ability_is_used = false;
public:
	GameManager(Game& game, InterfaceSymbols& registers) : game(game), registers(registers) {
		controller = new GameController(game);
		visualizer = new GameVisualizer(game);
	}
	~GameManager() {
		delete controller;
		delete visualizer;
	}

	void startGame() {
		game.startGame();
		while (game.isRunning()) {
			ICommand* command = input.readCommand(ability_is_used, registers);
			if(command != nullptr)
				if (command->is_interface)
					visualizer->acceptCommand(command);
				else
					controller->acceptCommand(command);
		}
		std::cout << "Game has finished!\n";
	}
};