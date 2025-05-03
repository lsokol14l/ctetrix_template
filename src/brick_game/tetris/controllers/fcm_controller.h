#ifndef __FCM_CONTROLLER_H__
#define __FCM_CONTROLLER_H__

#include "entities/board.h"
#include "entities/figure.h"
#include "entities/tetris_state.h"
#include "objects.h"

void on_start_state(UserAction_t sig, tetris_state *state, int *score,
                    int *level, int *high_score, board_t *board,
                    figure_t *figure, figure_t *next_figure);
void on_spawn_state(tetris_state *state, const board_t *board,
                    struct timespec *start_time, int score, int *level,
                    figure_t *figure, figure_t *next_figure);

void on_moving_state(UserAction_t sig, tetris_state *state, figure_t *figure,
                     const board_t *board, struct timespec *start_time,
                     int level);
void on_shifting_state(tetris_state *state, figure_t *figure,
                       const board_t *board);
void on_attaching_state(tetris_state *state, figure_t *figure, board_t *board,
                        int *score, int *level);

void on_game_over_state(UserAction_t sig, tetris_state *state, int score);

void on_pause_state(UserAction_t sig, tetris_state *state);

#endif  // __FCM_CONTROLLER_H__
