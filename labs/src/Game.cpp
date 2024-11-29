#include "../Game.h"

Game::Game(GameSettings& settings) : number_of_ships(settings.number_of_ships) {
	player.field = Battlefield(settings.length, settings.width, true);
	opp.field = Battlefield(settings.length, settings.width, false);
	player.manager = ShipManager(settings.number_of_ships);
	opp.manager = ShipManager(settings.number_of_ships);
}


void Game::printMessage(std::string message) {
	std::cout << message;
}
void Game::printSettingInfo() {
	player.manager.settingInfo();
}

void Game::printInfo(){
	printMessage("Your fleet:\n");
	player.manager.Info();
	printMessage("\nOpp's fleet:\n");
	opp.manager.Info();
}

void Game::placeShips() {
	printMessage("Set your ships:\n");
	while (player.manager.endOfSetting()) { // ! НЕ ЗАБЫТЬ ВЕРНУТЬ
		printSettingInfo();
		player.field.print();
		int length, x, y;
		char o;
		printMessage("Enter:\nLength of the chosen ship (from 1 to 4): ");
		std::cin >> length;
		printMessage("\nCoordinates of its upper left corner: ");
		std::cin >> x >> y;
		printMessage("\nOrientation (h/v: h = horizontal, v = vertical): ");
		std::cin >> o;
		Orientation orient = o == 'v' ? VERTICAL : HORIZONTAL;
			// throw std::invalid_argument();    ;обработчик ошибок There is only two genders!
		player.manager.placeShip(player.field, length, x - 1, y - 1, orient);
		std::cout << "=========\n";
	}
	
	int random_position_x, random_position_y;
	Orientation random_orientation;
	for (int length = 1; length <= 4; length++) {
		for (int j = 0; j < number_of_ships[length]; j++) {
			do {
				random_position_x = rand() % opp.field.length;
				random_position_y = rand() % opp.field.width;
				random_orientation = (rand() % 2 == 0 ? VERTICAL : HORIZONTAL); // случайно выбираем направление корабля
			} while (!player.field.isValidPosition(random_position_x, random_position_y, length, random_orientation)); // проверяем, можно ли поставить корабль на это место

			player.manager.placeShip(player.field, length, random_position_x, random_position_y, random_orientation);
		}
	}
}

void Game::spawnOpp() {
	opp.field.clear();
	opp.manager.reset();

	int random_position_x, random_position_y;
	Orientation random_orientation;
	for (int length = 1; length <= 4; length++) {
		for (int j = 0; j < number_of_ships[length]; j++) {
			do {
				random_position_x = rand() % opp.field.length;
				random_position_y = rand() % opp.field.width;
				random_orientation = (rand() % 2 == 0 ? VERTICAL : HORIZONTAL); // случайно выбираем направление корабля
			} while (!opp.field.isValidPosition(random_position_x, random_position_y, length, random_orientation)); // проверяем, можно ли поставить корабль на это место

			opp.manager.placeShip(opp.field, length, random_position_x, random_position_y, random_orientation);
		}
	}
}

void Game::startGame() {
	placeShips();
	spawnOpp();
	is_running = true;
}

void Game::checkAbilities() {
	std::cout << "Available ability is " << ability_manager.viewAbility() << '\n';
}

void Game::printInfoAbilities() {
	printMessage("There are 3 abilities in the game:\n\t0 - DoubleDamage. Your next attack will deal double damage\n");
	printMessage("\t1 - Scanner. Requires 2 arguments - x, y - coordinates. Check if there is a ship or not in the 2x2 square area.\n");
	printMessage("\t2 - Shelling. Hit random ship segment.\n");
}

void Game::useAbility() {
	std::pair<int, int> coords;
	IArgs* args;
	switch (ability_manager.viewAbility())
	{
	case 0:
		args = new DoubleDamageArgs(&opp.field);
		ability_manager.useAbility(*args);
		printMessage("Double damage is activated!\n");
		delete args;
		break;
	case 1:
		printMessage("Enter coordinates: ");
		std::cin >> coords.first >> coords.second;
		args = new ScannerArgs(coords, &opp.field);
		ability_manager.useAbility(*args);
		delete args;
		break;
	case 2:
		args = new ShellingArgs(&opp.manager);
		ability_manager.useAbility(*args);
		printMessage("That was hot! Now shelling is over, some enemy ship was damaged!\n");
		delete args;
		break;
	}
}


void Game::attack(std::pair<int, int> coords) {
	bool new_turn = opp.field.attack(coords.first-1, coords.second-1);
	if (opp.manager.updateInfo())
		ability_manager.createAbility();
	if (opp.manager.gameOver()) {
		printMessage("Congratulation! You managed to win this battle, but can you withstand a new attack?\nNew opponent has come!\n");
		spawnOpp();
	}
	if (!new_turn)
		oppsTurn();
	else
		printMessage("There is a hit! It's your turn again!\n");
}

void Game::oppsTurn() {
	printMessage("Opp's turn!\n");
	int x, y;
	x = rand() % player.field.length;
	y = rand() % player.field.width;
	std::cout << '(' << x+1 << ", " << y+1 << ") attacked\n";
	if (player.field.attack(x, y))
		if (player.manager.gameOver()) {
			gameOver();
		}
		else {
			printMessage("There is a hit!\nAgain, ");
			oppsTurn();
		}
}

void Game::gameOver() {
	printMessage("GAME OVER!!\nDo you want to restart? (y/n)\n");
	char answer;
	std::cin >> answer;
	if (answer == 'y') {
		player.field.clear();
		opp.field.clear();
		player.manager = ShipManager(number_of_ships);
		opp.manager = ShipManager(number_of_ships);
		startGame();
	}
	else if (answer == 'n') {
		is_running = false;
	}
	else {
		printMessage("Wrong argument!\n");
	}
}

void Game::printMyField() {
	player.field.print();
}

void Game::printOppsField() {
	opp.field.print();
}

bool Game::isRunning() { return is_running; };

void Game::saveGame() {
	state.saveGame();
}

void Game::loadGame() {
	state.loadGame();
}
