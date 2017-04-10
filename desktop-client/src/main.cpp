#include <game.h>

int main(int, char**) {
    Game game;
    /*
        I am planning on passing some settings here, like types of controls to use, etc.
        then again, most devices probably will be best with all control systems,
        maybe this will just dictate the screen size.
    */
    return game.run();
}
