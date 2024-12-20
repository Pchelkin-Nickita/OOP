#pragma once

#include "Game.h"


class DrawField {
private:
	Game& game;
	InterfaceSymbols registers;
public:
	DrawField(Game& game, InterfaceSymbols registers);

	void printMyField();
	void printOppsField();
};