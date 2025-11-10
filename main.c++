#include "headers.c++"
#include "game.c++"

int main() {
    Game* game = new Game(8);
    game -> printBoard();
    return 0;
}