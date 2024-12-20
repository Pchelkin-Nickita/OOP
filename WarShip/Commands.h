#pragma once

#include "Game.h"
#include "DrawField.h"

class ICommand {
public:
	bool is_interface = false;
	virtual void execute(Game& game) = 0;
};

class Attack : public ICommand {
	std::pair<int, int> coords;
public:
	Attack(std::pair<int, int> coords);
	void execute(Game& game) override;
};

class UseAbility : public ICommand {
public:
	void execute(Game& game) override;
};

class CheckAbility : public ICommand {
public:
	void execute(Game& game) override;
};

class InfoAbilities : public ICommand {
public:
	void execute(Game& game) override;
};

class Info : public ICommand {
public:
	void execute(Game& game) override;
};

class PrintMyField : public ICommand {
	InterfaceSymbols& registers;
public:
	PrintMyField(InterfaceSymbols& registers);
	void execute(Game& game);
};

class PrintOppsField : public ICommand {
	InterfaceSymbols& registers;
public:
	PrintOppsField(InterfaceSymbols& registers);
	void execute(Game& game);
};

class SaveGame : public ICommand {
public:
	void execute(Game& game) override;
};

class LoadGame : public ICommand {
public:
	void execute(Game& game) override;
};