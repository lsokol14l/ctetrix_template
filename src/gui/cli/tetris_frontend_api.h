#ifndef __TETRIS_FRONTEND_API_H__
#define __TETRIS_FRONTEND_API_H__

#include <stdbool.h>

#include "objects.h"

void init_gui();
void destroy_gui();
void get_action(UserAction_t *action, bool *hold);

void print_overlay();
void print_game(const GameInfo_t *game_info);

#endif  // __TETRIS_FRONTEND_API_H__
