#ifndef __TETRIS_CONTROLLER_H__
#define __TETRIS_CONTROLLER_H__

#include <stdbool.h>

#include "entities/board.h"
#include "entities/figure.h"
#include "objects.h"

void adjust_coordinates_on_board(figure_t *figure);

bool update_coordinate_if_possible(const figure_t *src, figure_t *dst,
                                   const board_t *board);
void init_board(board_t *board);
void spawn_figure(figure_t *figure);

void init_and_change_figures(figure_t *figure, figure_t *next_figure);
void init_figures_as_empty(figure_t *figure, figure_t *next_figure);
void init_empty_figure(figure_t *figure);

void rotate_figure_if_possible(figure_t *figure, const board_t *board);

void move_horizontal_figure_if_possible(figure_t *figure, const board_t *board,
                                        UserAction_t moving_signal);

void move_down_once_if_possible(figure_t *figure, const board_t *board);
void move_down_to_intersect(figure_t *figure, const board_t *board);

bool init_figure_on_board(figure_t *figure, const board_t *board);
void init_figure_on_info(figure_t *figure);
bool is_need_apply_figure_on_board(const figure_t *figure,
                                   const board_t *board);
void apply_figure_on_board(figure_t *figure, board_t *board,
                           size_t *count_distruction_row);

#endif  // __TETRIS_CONTROLLER_H__
