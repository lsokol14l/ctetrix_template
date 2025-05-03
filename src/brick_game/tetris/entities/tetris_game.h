#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

#include "board.h"
#include "figure.h"
#include "objects.h"
#include "tetris_state.h"

typedef struct {
  GameInfo_t game_info;

  tetris_state state;
  board_t board;
  figure_t figure;
  figure_t next_figure;

  int score;
  int high_score;
  int level;
  struct timespec start_time;

} tetris_game_t;

#endif  // __TETRIS_GAME_H__
