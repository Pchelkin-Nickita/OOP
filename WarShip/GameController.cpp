#include "GameController.h"

GameController::GameController(Game& game) : game(game) {}

void GameController::acceptCommand(ICommand* command) {
	if (command != nullptr)
		command->execute(game);
}