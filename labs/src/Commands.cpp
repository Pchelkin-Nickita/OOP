#include "../Commands.h"


Attack::Attack(std::pair<int, int> coords) : coords(coords) {}
void Attack::execute(class Game& game) {
	game.attack(coords);
}

void UseAbility::execute(class Game& game) {
	game.useAbility();
}

void CheckAbility::execute(class Game& game) {
	game.checkAbilities();
}

void InfoAbilities::execute(class Game& game) {
	game.printInfoAbilities();
}

void Info::execute(class Game& game) {
	game.printInfo();
}

void PrintMyField::execute(class Game& game) {
	game.printMyField();
}

void PrintOppsField::execute(class Game& game) {
	game.printOppsField();
}

void SaveGame::execute(class Game& game) {
	game.saveGame();
}


void LoadGame::execute(class Game& game) {
	game.loadGame();
}
