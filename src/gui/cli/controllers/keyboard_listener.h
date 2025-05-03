#ifndef __KEYBOARD_LISTENER_H__
#define __KEYBOARD_LISTENER_H__

#include "objects.h"

void validate_action(int user_input, UserAction_t *action, bool *hold);
int to_lower_case(int c);

#endif  // __KEYBOARD_LISTENER_H__
