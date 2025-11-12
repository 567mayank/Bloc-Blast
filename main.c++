#include "headers.c++"
#include "game_controller.c++"
int main() {
  GameController *controller = new GameController();
  controller->initApp();
  delete controller;
  return 0;
}