#ifndef __PRINT_CONTROLLER_H__
#define __PRINT_CONTROLLER_H__

#include "objects.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_common_rectangle();
void print_board_rectangle();
void print_info_rectangle();

void clear_in_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void clear_board_rectangle();
void clear_info_rectangle();

void print_board(const int **matrix);
void print_figure_on_info_table(const int **matrix);
void print_game_info(int level, int score, int high_score);

void print_start_state();
void print_game_over_state();
void print_pause_state();

void print_text_on_board(const char *str, int row_index);
void print_next_text_line_on_board(const char *str, int *row_index);

#endif  // __PRINT_CONTROLLER_H__
