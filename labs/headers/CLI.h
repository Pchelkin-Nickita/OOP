#pragma once

#include "Commands.h"

class CLIInput
{
public:
	CLIInput() = default;

	ICommand* readCommand(bool& ability_is_used);
};
