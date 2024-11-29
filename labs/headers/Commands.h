#pragma once

#include "Game.h"

class ICommand {
public:
	virtual void execute(Game& game) = 0;
};

class Attack : public ICommand {
	std::pair<int, int> coords;
public:
	Attack(std::pair<int, int> coords);
	void execute(class Game& game) override;
};

class UseAbility : public ICommand {
public:
	void execute(class Game& game) override;
};

class CheckAbility : public ICommand {
public:
	void execute(class Game& game) override;
};

class InfoAbilities : public ICommand {
public:
	void execute(class Game& game) override;
};

class Info : public ICommand {
public:
	void execute(class Game& game) override;
};

class PrintMyField : public ICommand {
public:
	void execute(class Game& game) override;
};

class PrintOppsField : public ICommand {
public:
	void execute(class Game& game) override;
};

class SaveGame : public ICommand {
public:
	void execute(class Game& game) override;
};

class LoadGame : public ICommand {
public:
	void execute(class Game& game) override;
};