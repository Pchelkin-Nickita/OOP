#include "InputVar.h"


CLIInput::CLIInput() {
	 std::ifstream load("commands.txt");
	 std::string line;
	 std::vector<char> scan_codes;

	 if (load.is_open()) {
		 while (std::getline(load, line, ' ')) {
			 if (std::find(scan_codes.begin(), scan_codes.end(), line[0]) != scan_codes.end())
				 break;
			 scan_codes.push_back(line[0]);
		 }
	 }
	 load.close();

	 if (scan_codes.size() == 9) {
		 commands = scan_codes;
	 }
	 else {
		 commands = { 'a', 'x', 'c', 'i', 'z', 'm', 'o', 's', 'l' };
	 }
}

ICommand* CLIInput::readCommand(bool& ability_is_used, InterfaceSymbols& registers) {
	std::cout << "\nEnter Command: ";
	ICommand* new_command = nullptr;
	char scan_key;
	std::cin >> scan_key;
	try
	{	
		int code = std::find(commands.begin(), commands.end(), scan_key) - commands.begin();
		std::pair<int, int> coords;
		switch (code)
		{
		case 0:
			std::cout << "Enter coordinates you want to attack: ";
			std::cin >> coords.first >> coords.second;
			new_command = new Attack(coords);
			break;
		case 1:
			if (ability_is_used) {
				std::cout << "You have already used your ability in this round!";
				break;
			}
			new_command = new UseAbility();
			break;
		case 2:
			new_command = new CheckAbility();
			new_command->is_interface = true;
			break;
		case 3:
			new_command = new Info();
			new_command->is_interface = true;
			break;
		case 4:
			new_command = new InfoAbilities();
			new_command->is_interface = true;
			break;
		case 5:
			new_command = new PrintMyField(registers);
			new_command->is_interface = true;
			break;
		case 6:
			new_command = new PrintOppsField(registers);
			new_command->is_interface = true;
			break;
		case 7:
			new_command = new SaveGame();
			break;
		case 8:
			new_command = new LoadGame();
			break;
		default:
			new_command = nullptr;
		}
	}
	catch (std::exception& e)
	{
		new_command = nullptr;
	}
	return new_command;
}