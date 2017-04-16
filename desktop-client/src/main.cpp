#include <game.h>

int main(int, char**) {
    Game* game = new Game(640, 480, 60);
    int returnValue = game->Run();
    delete game;
    return returnValue;
}
