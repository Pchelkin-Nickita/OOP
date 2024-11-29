#include "GameController.h"


GameController::GameController(Game& game) : game(game) {}

void GameController::startGame() {
	game.startGame();
	while (game.isRunning()) {
		acceptCommand(CLI.readCommand(ability_is_used));
	}
	std::cout << "Game has finished!\n";
}

void GameController::acceptCommand(ICommand* command) {
	if (command != nullptr)
		command->execute(game);
}