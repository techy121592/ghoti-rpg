#include <iostream>
#include <game.h>

int main(int, char**) {
    Game* game = new Game(640, 480, 60);
    int returnValue = game->Run();
    delete game;
    std::cout << "Game closed successfully" << std::endl;
    return returnValue;
}
