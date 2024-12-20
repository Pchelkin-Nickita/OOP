#include "DrawField.h"

DrawField::DrawField(Game& game, InterfaceSymbols registers) : game(game), registers(registers) {}

void DrawField::printMyField() {
	game.printMyField(registers);
}

void DrawField::printOppsField() {
	game.printOppsField(registers);
}