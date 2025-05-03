#include "objects.h"
#include "tetris.h"
#include "tetris_backend_api.h"
#include "tetris_frontend_api.h"

int main() {
  init();
  game_loop();
  end_game();
  return 0;
}

void init() {
  init_gui();
  print_overlay();
  init_game();
}

void game_loop() {
  UserAction_t action = Start;
  bool hold = true;
  GameInfo_t game_info = {0};

  get_action(&action, &hold);
  userInput(action, hold);

  game_info = updateCurrentState();
  while (game_info.pause != EXIT_GAME_INT_ENUM) {
    print_game(&game_info);

    get_action(&action, &hold);
    userInput(action, hold);
    game_info = updateCurrentState();
  }
}

void end_game() {
  destroy_game();
  destroy_gui();
}