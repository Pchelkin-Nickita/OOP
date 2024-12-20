#include "Commands.h"


Attack::Attack(std::pair<int, int> coords) : coords(coords) {}
void Attack::execute(Game& game) {
	game.attack(coords);
}

void UseAbility::execute(Game& game) {
	game.useAbility();
}

void CheckAbility::execute(Game& game) {
	game.checkAbilities();
}

void InfoAbilities::execute(Game& game) {
	game.printInfoAbilities();
}

void Info::execute(Game& game) {
	game.printInfo();
}

PrintMyField::PrintMyField(InterfaceSymbols& registers) : registers(registers) {}
void PrintMyField::execute(Game& game) {
	DrawField* drawer = new DrawField(game, registers);
	drawer->printMyField();
}

PrintOppsField::PrintOppsField(InterfaceSymbols& registers) : registers(registers) {}
void PrintOppsField::execute(Game& game) {
	DrawField* drawer = new DrawField(game, registers);
	drawer->printOppsField();
}

void SaveGame::execute(Game& game) {
	game.saveGame();
}


void LoadGame::execute(Game& game) {
	game.loadGame();
}
