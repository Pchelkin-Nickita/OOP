#pragma once
#include "Commands.h"

class IInputVar {
public:
	virtual ICommand* readCommand(bool& ability_is_used, InterfaceSymbols& registers) = 0;
};


class CLIInput : public IInputVar
{
private:
	std::vector<char> commands;
public:
	CLIInput();

	ICommand* readCommand(bool& ability_is_used, InterfaceSymbols& registers) override;
};
