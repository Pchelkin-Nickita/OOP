#include <iostream>
#include "GameManager.h"


int main() {
    srand(time(0)); 
    
    GameSettings settings = { 4, 4,  { {1, 2} } };
    InterfaceSymbols registers;

    Game game(settings);
    GameManager<CLIInput> manager(game, registers);

    manager.startGame();

    return 0;
}