#include <iostream>
#include <game.h>
#include <thread_pool.h>

int main(int, char**) {
    ThreadPool::Init(4, 1);
    Game* game = new Game(640, 480, 60);

    int returnValue = game->Run();
    delete game;
    std::cout << "Game closed successfully" << std::endl;
    return returnValue;
}
