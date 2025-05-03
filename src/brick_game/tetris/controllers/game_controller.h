#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "entities/tetris_game.h"

tetris_game_t *get_game();

void fill_game_info_board();
void fill_game_info_figure_on_board();
void fill_game_info_table_zeros();
void fill_game_info_next_figure_on_info_table();
void fill_game_info_game_state();

int **alloc_matrix(int rows, int columns);

#endif  // __GAME_CONTROLLER_H__
