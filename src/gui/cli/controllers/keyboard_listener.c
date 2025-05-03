#include "keyboard_listener.h"

#include <ncurses.h>
#include <stdbool.h>

#include "tetris_frontend_api.h"
#include "tetris_frontend_defines.h"

void get_action(UserAction_t *action, bool *hold) {
  *hold = true;

  int action_char = getch();
  if (action_char != EOF) {
    validate_action(action_char, action, hold);
  } else {
    *hold = true;
  }
}

void validate_action(int user_input, UserAction_t *action, bool *hold) {
  *hold = false;

  if (user_input == KEY_UP || to_lower_case(user_input) == KEY_UP_VIM_PACK)
    *action = Up;
  else if (user_input == KEY_DOWN ||
           to_lower_case(user_input) == KEY_DOWN_VIM_PACK)
    *action = Down;
  else if (user_input == KEY_LEFT ||
           to_lower_case(user_input) == KEY_LEFT_VIM_PACK)
    *action = Left;
  else if (user_input == KEY_RIGHT ||
           to_lower_case(user_input) == KEY_RIGHT_VIM_PACK)
    *action = Right;
  else if (user_input == S21_SPACE_KEY || user_input == S21_ENTER_KEY)
    *action = Action;
  else if (user_input == S21_ESCAPE)
    *action = Terminate;
  else if (to_lower_case(user_input) == S21_PAUSE_KEY)
    *action = Pause;
  else if (to_lower_case(user_input) == S21_START_KEY)
    *action = Start;
  else {
    *hold = true;
  }
}

int to_lower_case(int c) {
  if (c >= 'A' && c <= 'Z') {
    c = c + 32;
  }
  return c;
}
