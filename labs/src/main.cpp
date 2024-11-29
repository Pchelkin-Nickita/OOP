#include <iostream>
#include "GameController.h"


int main() {
    srand(time(0)); 
    
    GameSettings settings = { 4, 4,  { {1, 2} } };
    Game game = Game(settings);
    GameController controller = GameController(game);
    controller.startGame();
    return 0;
}