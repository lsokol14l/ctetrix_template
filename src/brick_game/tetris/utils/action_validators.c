#include "action_validators.h"

bool is_horizontal_move_signal(UserAction_t action_signal) {
  return action_signal == Right || action_signal == Left;
}