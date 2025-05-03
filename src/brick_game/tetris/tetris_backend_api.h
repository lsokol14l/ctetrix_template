#ifndef __TETRIS_BACKEND_API_H__
#define __TETRIS_BACKEND_API_H__

#include <stdbool.h>

#include "objects.h"

void init_game();
void destroy_game();

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif  // __TETRIS_BACKEND_API_H__
