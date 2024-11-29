#include "../CLI.h"


ICommand* CLIInput::readCommand(bool& ability_is_used) {
	std::cout << "\nEnter Command: ";
	ICommand* new_command = nullptr;
	char scan_key;
	std::cin >> scan_key;
	try
	{	
		std::pair<int, int> coords;
		switch (scan_key)
		{
		case 'a':
			std::cout << "Enter coordinates you want to attack: ";
			std::cin >> coords.first >> coords.second;
			new_command = new Attack(coords);
			break;
		case 'x':
			if (ability_is_used) {
				std::cout << "You have already used your ability in this round!";
				break;
			}
			new_command = new UseAbility();
			break;
		case 'c':
			new_command = new CheckAbility();
			break;
		case 'i':
			new_command = new Info();
			break;
		case 'z':
			new_command = new InfoAbilities();
			break;
		case 'm':
			new_command = new PrintMyField();
			break;
		case 'o':
			new_command = new PrintOppsField();
			break;
		case 's':
			new_command = new SaveGame();
			break;
		case 'l':
			new_command = new LoadGame();
			break;
		}
	}
	catch (std::exception& e)
	{
		new_command = nullptr;
	}
	return new_command;
}
